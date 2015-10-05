/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
//PUBLIC_HEADER
#pragma once

#include "Value.h"

namespace mscl
{
	//Title: Histogram

	//API Class: Bin
	//	Represents a single bin within a Histogram.
	class Bin
	{
	public:
		//API Constructor: Bin
		//	Creates a Bin object.
		//
		//Parameters:
		//	start - The start of the range of the bin.
		//	end - The end of the range of the bin (non-inclusive).
		//	count - The number of values that fall within the range of this bin.
		Bin(const Value& start, const Value& end, uint32 count);

	private:
		Bin();						//default constructor disabled

	private:
		//Variable: m_start
		//	The start of the range of the bin.
		Value m_start;

		//Variable: m_end
		//	The end of the range of the bin (non-inclusive).
		Value m_end;

		//Variable: m_count
		//	The number of values that fall within the range of this bin.
		uint32 m_count;

	public:
		//API Function: start
		//	Gets the start of the range of the bin.
		//
		//Returns:
		//	The start of the range of the bin, as a <Value> object.
		Value start() const;

		//API Function: end
		//	Gets the end of the range of the bin (non-inclusive).
		//
		//Returns:
		//	The end of the range of the bin, as a <Value> object.
		Value end() const;

		//API Function: count
		//	Gets the number of values that fall within the range of this bin.
		//
		//Returns:
		//	The number of values that fall within the range of this bin.
		uint32 count() const;
	};

	//API Typedef: Bins
	//	Typedef for a vector of <Bin> objects.
	typedef std::vector<Bin> Bins;

	
	//API Class: Histogram
	//	Represents a Histogram object.
	class Histogram
	{
	private:
		Histogram();	//disable default constructor

	public:
		//API Constructor: Histogram
		//	Creates a Histogram object with no bins.
		//
		//Parameters:
		//	
		Histogram(const Value& binsStart, const Value& binsSize);

	private:
		//Variable: m_binsStart
		//	The value of the start of the first Bin in the Histogram.
		Value m_binsStart;
		
		//Variable: m_binsSize
		//	The size of each Bin in the Histogram.
		Value m_binsSize;

		//Variable: m_bins
		//	The <Bins> that are contained within this Histogram.
		Bins m_bins;

	public:
		//API Function: binsStart
		//	Gets the value of the start of the first Bin in the Histogram.
		//
		//Returns:
		//	The start of the first Bin in the Histogram.
		Value binsStart() const;

		//API Function: binsSize
		//	Gets the size of each Bin in the Histogram.
		//
		//Returns:
		//	The size of each Bin in the Histogram.
		Value binsSize() const;

		//API Function: bins
		//	Gets the <Bins> contained within this Histogram.
		//
		//Returns:
		//	A <Bins> object containing each bin within this Histogram.
		Bins bins() const;

		//API Function: addBin
		//	Adds a single <Bin> to the Histogram.
		//	The first Bin's start value should match the binsStart used in the constructor.
		//	Every Bin added should have the same size which matches the binsSize used in the constructor.
		//
		//Parameters:
		//	bin - The <Bin> to add to the Histogram.
		void addBin(const Bin& bin);
	};
}