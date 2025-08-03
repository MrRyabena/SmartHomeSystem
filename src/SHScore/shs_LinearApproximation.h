#pragma once

/*
  Last update: v2.3.0
  Versions:
    v2.3.0 — created.
*/


#include <stdint.h>
#include <functional>

#include "shs_types.h"


namespace shs
{
    template <typename Accumulate_T = shs::t::shs_double_t>
    class LinearApproximation;
}


/**
 * @class LinearApproximation
 * @brief Class for linear approximation by the least squares method.
 *
 * This class implements linear regression using the method of least squares.
 * It can accumulate data points and calculate the coefficients of the linear equation y = ax + b
 * that best fits the data points.
 *
 * The class uses incremental calculation to avoid storing all data points in memory,
 * making it suitable for real-time applications with large datasets.
 *
 * @tparam Accumulate_T The data type used for internal calculations (default: shs::t::shs_double_t)
 *
 * @version 2.3.0
 * @date Last updated: v2.3.0
 */
template <typename Accumulate_T>
class shs::LinearApproximation
{
public:

    /**
     * @brief Adds a data point to the approximation calculation.
     *
     * @tparam Coord_T The data type for coordinates
     *
     * @param x The x-coordinate of the data point
     * @param y The y-coordinate of the data point
     */
    template <typename Coord_T>
    void addPoint(const Coord_T x, const Coord_T y)
    {
        m_sumX += x;
        m_sumY += y;
        m_sumX2 += x * x;
        m_sumXY += x * y;
        m_data_size++;
    }

    /**
     * @brief Adds a data point using a point structure.
     *
     * @tparam Point_T The point structure type
     * @param point A structure containing x and y members
     */
    template <typename Point_T>
    void addPoint(const Point_T& point) { addPoint(point.x, point.y); }

    /**
     * @brief Adds a value with automatic x-coordinate generation.
     *
     * The x-coordinate is automatically set to the current number of data points.
     * Useful for time series data where x represents time/index.
     *
     * @tparam Coord_T The data type for the value
     * @param value The y-coordinate value
     */
    template <typename Coord_T>
    void addValue(const Coord_T value) { addPoint(value, static_cast<Coord_T>(m_data_size)); }

    /**
     * @brief Calculates and returns the linear approximation coefficients.
     *
     * Returns the coefficients (a, b) of the linear equation y = ax + b
     * that best fits the accumulated data points using the method of least squares.
     *
     * @return std::pair<Accumulate_T, Accumulate_T> The coefficients (a, b) where:
     *         - first: slope coefficient (a)
     *         - second: y-intercept coefficient (b)
     *
     * @note Requires at least 2 data points for meaningful results.
     *       Returns (0, 0) if insufficient data.
     */
    [[nodiscard]] std::pair<Accumulate_T, Accumulate_T> approximate() const
    {
        Accumulate_T a = m_sumXY * m_data_size - m_sumX * m_sumY;
        a /= m_sumX2 * m_data_size - m_sumX * m_sumX;

        Accumulate_T b = m_sumY - a * m_sumX;
        b /= m_data_size;

        return { a, b };
    }

    /**
     * @brief Clears all accumulated data and resets the approximation.
     *
     * Resets all internal sums and counters to zero, effectively
     * starting a new approximation calculation.
     */
    void clear()
    {
        m_sumX = 0;
        m_sumY = 0;
        m_sumX2 = 0;
        m_sumXY = 0;
        m_data_size = 0;
    }


    /**
     * @brief Static method to calculate linear approximation from existing data arrays.
     *
     * Performs linear regression on two arrays of data points without storing
     * the data in the class instance. Useful for one-time calculations.
     *
     * @tparam Accumulate_T The data type for coordinates
     * @tparam It Iterator type for the data arrays
     * @tparam Size_T The type for data size
     *
     * @param xs Iterator to the beginning of x-coordinates array
     * @param ys Iterator to the beginning of y-coordinates array
     * @param data_size Number of data points in the arrays
     *
     * @return std::pair<Coord_T, Coord_T> The coefficients (a, b) of y = ax + b
     *
     * @note Requires at least 2 data points for meaningful results.
     *       Arrays must have the same size and valid iterators.
     */
    template <typename Accumulate_T, typename It, typename Size_T>
    [[nodiscard]] static std::pair<Accumulate_T, Accumulate_T> approximate(It xs, It ys, Size_T data_size)
    {
        Accumulate_T sumX{}, sumY{}, sumX2{}, sumXY{};

        for (Size_T i = 0; i < data_size; i++)
        {
            sumX += *xs;
            sumY += *ys;
            sumX2 += *xs * *xs;
            sumXY += *xs * *ys;
            xs++;
            ys++;
        }

        Accumulate_T a = data_size * sumXY - sumX * sumY;
        a /= data_size * sumX2 - sumX * sumX;

        Accumulate_T b = sumY - a * sumX;
        b /= data_size;

        return std::pair<Accumulate_T, Accumulate_T>(a, b);
    }

private:
    /** @brief Sum of all x-coordinates */
    Accumulate_T m_sumX{};
    /** @brief Sum of all y-coordinates */
    Accumulate_T m_sumY{};
    /** @brief Sum of squares of x-coordinates */
    Accumulate_T m_sumX2{};
    /** @brief Sum of products of x and y coordinates */
    Accumulate_T m_sumXY{};
    /** @brief Number of accumulated data points */
    size_t m_data_size{};

};
