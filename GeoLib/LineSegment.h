/**
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 */

#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "Point.h"

namespace GeoLib
{

class LineSegment final
{
public:
	/// Constructs a line segment given by its begin and end points.
	/// @remark The main purpose of class LineSegment is the use within a
	/// polyline. For this reason the memory is not managed per default. But the
	/// user has the freedom to hand over the responsibility for the mem
	/// managment of the points to the object.
	LineSegment(GeoLib::Point* const beg, GeoLib::Point* const end,
	            bool point_mem_management_by_line_segment = false);

	LineSegment(LineSegment&& line_segment);
	LineSegment(LineSegment const& line_segment);

	~LineSegment();

	LineSegment& operator= (LineSegment const& rhs) = delete;

	GeoLib::Point const& getBeginPoint() const;
	GeoLib::Point & getBeginPoint();

	GeoLib::Point const& getEndPoint() const;
	GeoLib::Point & getEndPoint();

private:
	GeoLib::Point* _a = nullptr;
	GeoLib::Point* _b = nullptr;
	bool _point_mem_management_by_line_segment = false;
};

std::ostream& operator<< (std::ostream& os, LineSegment const& s);

std::ostream& operator<<(std::ostream& os,
                         std::pair<GeoLib::LineSegment const&,
                                   GeoLib::LineSegment const&> const& seg_pair);
}
#endif
