/*******************************************************************************
 *                                                                             *
 * This file is part of the EMP Impulse project                                *
 *                                                                             *
 * Copyright (C) 2010 ElectroMagnetic Potatoes (EMP)                           *
 * See the AUTHORS file for more information.                                  *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                             *
 ******************************************************************************/

#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <common.hpp>

namespace math {

/**
 * \class Random
 * \brief The Random class provides a pseudorandom number generator.
 * \author Jonathan Giroux
 * 
 * It is based on a simple but efficient linear congruential generator.
 * Therefore it may be sufficient for simple applications but it may not be
 * suitable for advanced applications requiring a high-quality randomness.
 */
class IMPULSE_MATH_EXPORT Random
{
	public:

		/**
		 * \brief Constructs a pseudorandom number generator.
		 *
		 * The seed is taken from a system function. Therefore there is no
		 * warranty of difference between the seed of different objects.
		 */
		Random();

		/**
		 * \brief Constructs a pseudorandom number generator, given a seed.
		 * \param seed iniatial seed.
		 */
		Random(u32 seed);

		/**
		 * \brief Generates a new seed.
		 *
		 * The seed is taken from a system function. Therefore there is no
		 * warranty of difference between the seed of different objects.
		 */
		void regenerateSeed();

		/**
		 * \brief Sets a new seed.
		 * \param seed new seed.
		 */
		void setSeed(u32 seed);

		/**
		 * \brief Generates a new pseudorandom number.
		 *
		 * This function does not return the number, therefore there is no way
		 * to get it. Use this function to skip numbers.
		 */
		void next();

		/**
		 * \brief Returns a new pseudorandom boolean.
		 * \return pseudorandom, uniformly distributed boolean.
		 */
		bool nextBool();

		/**
		 * \brief Returns a new pseudorandom float.
		 * \param min minimal value (default is 0).
		 * \param max maximal value (default is 1).
		 * \return pseudorandom, uniformly distributed \c f32 value in range
		 * [\a min, \a max[.
		 *
		 * There is no warranty of accuracy on the small decimals.
		 */
		f32 nextF32(f32 min = 0.0f, f32 max = 1.0f);

		/**
		 * \brief Returns a new pseudorandom signed integer.
		 * \param min minimal value.
		 * \param max maximal value.
		 * \return pseudorandom, uniformly distributed \c i32 value in range
		 * [\a min, \a max[.
		 *
		 * \note This function relies on floating-point arithmetic. When working
		 * with range [0, 2^n[, consider the code below, faster and more
		 * accurate.
		 * \code
		 * nextU32() >> (32 - n)
		 * \endcode
		 */
		i32 nextI32(i32 min, i32 max);

		/**
		 * \brief Returns a new pseudorandom unsigned integer.
		 * \return pseudorandom, uniformly distributed \c u32 value in its
		 * maximal range [\c 0x00000000, \c 0xFFFFFFFF].
		 */
		u32 nextU32();
		
	private:
		
		/**
		 * \brief Actual seed.
		 */
		u32 seed;
};

} // math namespace

#endif // __RANDOM_HPP__
