/*
Пояснение к решению.

Программа писалась с минимальными затратами времени, поэтому вывод данных и прочее сделано без украшательств,
отсутствуют проверки на ошибки времени исполнения.

Вывод тех вычисленных значений, вывод которых не требуется, не делается. Значения проверяются в Debug.

В задании указано, что параметр t - берется вдоль кривой, однако не указано из каких соображений кроме 
helix. Там из приведенного примера ясно, что при изменении t на 2PI координаты x и y повторяются. Для 
дугих кривых использовал то же правило: t - угол в XOY в полярных координатах.

Радиусы задаю положительными значениями больше 1. Для простоты задаю step > 0.
*/

#include <iostream>

#include <Circle.h>
#include <Ellipse.h>
#include <Helix.h>

#include <vector>
#include <algorithm>

#include <omp.h>

#define CURVES_COUNT 1024
#define RADIUS_MAX 256 - 1
#define STEP_MAX 256
#define PI_4 0.785398

static size_t getRand_N(size_t nRange_)
{
    return size_t(std::rand() * nRange_ / RAND_MAX);
}

static double getRand_F(size_t nRange_)
{
    return 1.0 * std::rand() * nRange_ / RAND_MAX;
}

static void print(const char* sMessage_, const Curves::Point3D& point_)
{
    std::cout << sMessage_ << " : ";

    std::cout << point_.x << ", ";
    std::cout << point_.y << ", ";
    std::cout << point_.z << ".";

    std::cout << std::endl;
}

int main()
{
    std::srand((unsigned int)std::time(nullptr));

    std::vector<Curves::Curves3D* > m_vCurve;

    for (int i = 0; i < CURVES_COUNT; ++i)
    {
        switch (getRand_N(3))
        {
        case 0 : m_vCurve.push_back(new Curves::Circle(getRand_F(RADIUS_MAX) + 1)); break;
        case 1 : m_vCurve.push_back(new Curves::Ellipse(getRand_F(RADIUS_MAX) + 1, getRand_F(RADIUS_MAX) + 1)); break;
        case 2 : m_vCurve.push_back(new Curves::Helix(getRand_F(RADIUS_MAX) + 1, getRand_F(STEP_MAX))); break;
        default: break;
        }
    }

    for (Curves::Curves3D* pCurve : m_vCurve)
    {
        Curves::Point3D point_PI_4 = pCurve->getPoint(PI_4);
        print("coordinates of points at t=PI/4", point_PI_4);

        Curves::Point3D derivative_PI_4 = pCurve->getDerivative(PI_4);
        print("derivative at t=PI/4", derivative_PI_4);
    }

    std::vector<Curves::Circle* > m_vCircle;

    for (Curves::Curves3D* pCurve : m_vCurve)
    {
        Curves::Circle* pCircle = dynamic_cast<Curves::Circle* >(pCurve);
        if (!!pCircle)
            m_vCircle.push_back(pCircle);
    }

    std::sort(m_vCircle.begin(), m_vCircle.end(), [](Curves::Circle* a_, Curves::Circle* b_) { return a_->getRadius() < b_->getRadius(); });

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
            fRadiusSum += m_vCircle[nCurrentThread * nElementsInOririginalThread + i]->getRadius();
    }

    for (Curves::Curves3D* pCurve : m_vCurve)
        delete pCurve;
}
