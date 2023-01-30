#include <iostream>

#include <Circle.h>
#include <Ellipse.h>
#include <Helix.h>

#include <vector>
#include <algorithm>

#include <omp.h>

//-----------------------------------------------------------------------------------------------------------

const int nCurvesCount = 1024;
const int nRadiuMax = 256;
const int nStepMax = 256;
const double fPiBy4 = 0.785398;

//-----------------------------------------------------------------------------------------------------------

static inline double getRand(size_t nRange_)
{
    return 1.0 * std::rand() / RAND_MAX * nRange_;
}

static inline void print(const char* sMessage_, const Curves::Point3D& point_)
{
    std::cout << sMessage_ << " : " << point_.x << ", " << point_.y << ", " << point_.z << "." << std::endl;
}

static inline const Curves::Circle* toCircle(Curves::Curves3DConstPtr pCurve_)
{
    return dynamic_cast<const Curves::Circle*>(pCurve_.get());
}

//-----------------------------------------------------------------------------------------------------------

int main()
{
    std::srand((unsigned int)std::time(nullptr));

    std::vector<Curves::Curves3DConstPtr> m_vCurve;

    for (int i = 0; i < nCurvesCount; ++i)
    {
        switch (size_t(getRand(3)))
        {
        case 0 : m_vCurve.push_back(Curves::Circle::Create(getRand(nRadiuMax) + 1)); break;
        case 1 : m_vCurve.push_back(Curves::Ellipse::Create(getRand(nRadiuMax) + 1, getRand(nRadiuMax) + 1)); break;
        case 2 : m_vCurve.push_back(Curves::Helix::Create(getRand(nRadiuMax) + 1, getRand(nStepMax))); break;
        default: break;
        }
    }

    //-----------------------------------------------------------------------------------------------------------

    for (Curves::Curves3DConstPtr& pCurve : m_vCurve)
    {
        Curves::Point3D point_PI_4 = pCurve->getPoint(fPiBy4);
        print("coordinates of points at t=PI/4", point_PI_4);

        Curves::Point3D derivative_PI_4 = pCurve->getDerivative(fPiBy4);
        print("derivative at t=PI/4", derivative_PI_4);
    }

    //-----------------------------------------------------------------------------------------------------------

    std::vector<Curves::Curves3DConstPtr> m_vCircle;

    for (Curves::Curves3DConstPtr& pCurve : m_vCurve)
        if (!!toCircle(pCurve))
            m_vCircle.push_back(pCurve);

    std::sort(m_vCircle.begin(), m_vCircle.end(), 
        [](auto a_, auto b_) { return toCircle(a_)->getRadius() < toCircle(b_)->getRadius(); });

    //-----------------------------------------------------------------------------------------------------------

    size_t nThreadCount = std::min<size_t>(omp_get_max_threads(), m_vCircle.size());
    size_t nElementsInOririginalThread = m_vCircle.size() / nThreadCount;
    size_t nElementsInMasterThread = nElementsInOririginalThread + m_vCircle.size() - nElementsInOririginalThread * nThreadCount;

    double fRadiusSum = 0;

    omp_set_dynamic(0);

#pragma omp parallel num_threads((int)nThreadCount) reduction(+: fRadiusSum)
    {
        int nCurrentThread = omp_get_thread_num();

        size_t nElementCount = (nCurrentThread == nThreadCount - 1) ? nElementsInMasterThread : nElementsInOririginalThread;

        for (size_t i = 0; i < nElementCount; ++i)
            fRadiusSum += toCircle(m_vCircle[nCurrentThread * nElementsInOririginalThread + i])->getRadius();
    }

    std::cout << "Total sum of radius: " << fRadiusSum << std::endl;
}
