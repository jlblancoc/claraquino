/*****************************************************************************************
 FILE: circular_buffer.h
 PURPOSE: Implements efficient, 2^N-length, circular buffer of bytes.

Jose Luis Blanco Claraco (C) 2005-2017
Universidad de Malaga
Universidad de Almeria
****************************************************************************************/
#pragma once

#include <stdint.h>

/** A circular buffer of fixed size (defined at construction-time).
  * Length is 2^num_bits. For example num_bits=6 ==> length = 2^6=64 bytes
  * Optimized for 8bit cores. Limitation: num_bits<=8
  */
template <uint8_t num_bits = 6, uint8_t m_size = (1 << num_bits), uint8_t m_size_mask = (1 << num_bits)-1>
class circular_buffer
{
private:
	uint8_t   m_data[m_size];
	uint8_t   m_next_read,m_next_write;

public:
	circular_buffer() :
		m_next_read(0),
		m_next_write(0)
	{
		static_assert(num_bits>1 && num_bits<=8, "Template parameter num_bits must be between 2 and 8");
	}

	/** Insert a copy of the given element in the buffer.
	  * \return false If the buffer run out of space.
	  */
	bool push(uint8_t d)
	{
		uint8_t next_wr_idx = m_next_write+1;
		next_wr_idx &= m_size_mask;
		bool buf_overflow = (next_wr_idx==m_next_read);
		if (!buf_overflow)
		{
			m_data[m_next_write]=d;
			m_next_write = next_wr_idx;
		}
		return !buf_overflow;
	}

	/** Insert an array of elements in the buffer.
		* \exception std::out_of_range If the buffer run out of space.
		*/
	inline void push_many(uint8_t *array_elements, size_t count) 
	{
		while (count--)
			push(*array_elements++);
	}

	/** Retrieve an element from the buffer.
		* \return false if the buffer was empty.
		*/
	bool pop(uint8_t &out_val) 
	{
		if (m_next_read==m_next_write)
			return false;

		out_val=m_data[m_next_read++];
		m_next_read &= m_size_mask;
		return true;
	}

	/** peek, seeking ahead in the buffer (index=0 means the immediate next element, index=1 the following one, etc.)
	  * \return false If trying to read passing the number of available elements. */
	bool peek(size_t index, uint8_t &out_value) const {
		if (index>=this->size()) return false;
		out_value = m_data[(m_next_read + index) & m_size_mask];
		return true;
	}

	/** Return the number of elements available for read ("pop") in the buffer (this is NOT the maximum size of the internal buffer)
		* \sa capacity */
	uint8_t size() const
	{
		if (m_next_write>=m_next_read)
				return m_next_write-m_next_read;
		else	return m_next_write + (m_size-m_next_read);
	}

	/** Return the maximum capacity of the buffer.
		* \sa size
		*/
	uint8_t capacity() const {
		return m_size;
	}

	/** The maximum number of elements that can be written ("push") without rising an overflow error.
		*/
	uint8_t available() const {
		return (capacity()-size())-1;
	}

	/** Delete all the stored data, if any. */
	void clear() {
		m_next_write = m_next_read = 0;
	}

};  // end class circular_buffer
