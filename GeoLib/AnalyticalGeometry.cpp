/**
 * \file
 * \author Thomas Fischer
 * \date   2010-03-17
 * \brief  Implementation of analytical geometry functions.
 *
 * \copyright
 * Copyright (c) 2012-2016, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include "AnalyticalGeometry.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include <logog/include/logog.hpp>

#include "Polyline.h"
#include "PointVec.h"

#include "MathLib/LinAlg/Solvers/GaussAlgorithm.h"

extern double orient2d(double *, double *, double *);

namespace ExactPredicates
{
double getOrientation2d(MathLib::Point3d const& a,
    MathLib::Point3d const& b, MathLib::Point3d const& c)
{
    return orient2d(const_cast<double*>(a.getCoords()),
        const_cast<double*>(b.getCoords()),
        const_cast<double*>(c.getCoords()));
}
}

namespace GeoLib
{
Orientation getOrientation(const double& p0_x, const double& p0_y, const double& p1_x,
                           const double& p1_y, const double& p2_x, const double& p2_y)
{
    double h1((p1_x - p0_x) * (p2_y - p0_y));
    double h2((p2_x - p0_x) * (p1_y - p0_y));

    double tol(std::numeric_limits<double>::epsilon());
    if (fabs(h1 - h2) <= tol * std::max(fabs(h1), fabs(h2)))
        return COLLINEAR;
    if (h1 - h2 > 0.0)
        return CCW;

    return CW;
}

Orientation getOrientation(const GeoLib::Point* p0, const GeoLib::Point* p1,
                           const GeoLib::Point* p2)
{
    return getOrientation((*p0)[0], (*p0)[1], (*p1)[0], (*p1)[1], (*p2)[0], (*p2)[1]);
}

bool parallel(MathLib::Vector3 v, MathLib::Vector3 w)
{
    const double eps(std::numeric_limits<double>::epsilon());

    // check degenerated cases
    if (v.getLength() < eps)
        return false;

    if (w.getLength() < eps)
        return false;

    v.normalize();
    w.normalize();

    bool parallel(true);
    if (std::abs(v[0]-w[0]) > eps)
        parallel = false;
    if (std::abs(v[1]-w[1]) > eps)
        parallel = false;
    if (std::abs(v[2]-w[2]) > eps)
        parallel = false;

    if (! parallel) {
        parallel = true;
        // change sense of direction of v_normalised
        v *= -1.0;
        // check again
        if (std::abs(v[0]-w[0]) > eps)
            parallel = false;
        if (std::abs(v[1]-w[1]) > eps)
            parallel = false;
        if (std::abs(v[2]-w[2]) > eps)
            parallel = false;
    }

    return parallel;
}

bool lineSegmentIntersect(GeoLib::LineSegment const& s0,
                          GeoLib::LineSegment const& s1,
                          GeoLib::Point& s)
{
    GeoLib::Point const& a{s0.getBeginPoint()};
    GeoLib::Point const& b{s0.getEndPoint()};
    GeoLib::Point const& c{s1.getBeginPoint()};
    GeoLib::Point const& d{s1.getEndPoint()};

    if (!isCoplanar(a, b, c, d))
        return false;

    // handle special cases here to avoid computing intersection numerical
    if (MathLib::sqrDist(a, c) < std::numeric_limits<double>::epsilon() ||
        MathLib::sqrDist(a, d) < std::numeric_limits<double>::epsilon()) {
        s = a;
        return true;
    }
    if (MathLib::sqrDist(b, c) < std::numeric_limits<double>::epsilon() ||
        MathLib::sqrDist(b, d) < std::numeric_limits<double>::epsilon()) {
        s = b;
        return true;
    }

    MathLib::Vector3 const v(a, b);
    MathLib::Vector3 const w(c, d);
    MathLib::Vector3 const qp(a, c);
    MathLib::Vector3 const pq(c, a);

    auto isLineSegmentIntersectingAB = [&v](MathLib::Vector3 const& ap,
                                            std::size_t i)
    {
        // check if p is located at v=(a,b): (ap = t*v, t in [0,1])
        if (0.0 <= ap[i] / v[i] && ap[i] / v[i] <= 1.0) {
            return true;
        }
        return false;
    };

    if (parallel(v,w)) { // original line segments (a,b) and (c,d) are parallel
        if (parallel(pq,v)) { // line segment (a,b) and (a,c) are also parallel
            // Here it is already checked that the line segments (a,b) and (c,d)
            // are parallel. At this point it is also known that the line
            // segment (a,c) is also parallel to (a,b). In that case it is
            // possible to express c as c(t) = a + t * (b-a) (analog for the
            // point d). Since the evaluation of all three coordinate equations
            // (x,y,z) have to lead to the same solution for the parameter t it
            // is sufficient to evaluate t only once.

            // Search id of coordinate with largest absolute value which is will
            // be used in the subsequent computations. This prevents division by
            // zero in case the line segments are parallel to one of the
            // coordinate axis.
            std::size_t i_max(std::abs(v[0]) <= std::abs(v[1]) ? 1 : 0);
            i_max = std::abs(v[i_max]) <= std::abs(v[2]) ? 2 : i_max;
            if (isLineSegmentIntersectingAB(qp, i_max)) {
                s = c;
                return true;
            }
            MathLib::Vector3 const ad(a, d);
            if (isLineSegmentIntersectingAB(ad, i_max)) {
                s = d;
                return true;
            }
            return false;
        }
        return false;
    }

    // general case
    const double sqr_len_v(v.getSqrLength());
    const double sqr_len_w(w.getSqrLength());

    MathLib::DenseMatrix<double> mat(2,2);
    mat(0,0) = sqr_len_v;
    mat(0,1) = -1.0 * MathLib::scalarProduct(v,w);
    mat(1,1) = sqr_len_w;
    mat(1,0) = mat(0,1);

    double rhs[2] = {MathLib::scalarProduct(v,qp), MathLib::scalarProduct(w,pq)};

    MathLib::GaussAlgorithm<MathLib::DenseMatrix<double>, double*> lu;
    lu.solve(mat, rhs, true);

    // no theory for the following tolerances, determined by testing
    // lower tolerance: little bit smaller than zero
    const double l(-1.0*std::numeric_limits<float>::epsilon());
    // upper tolerance a little bit greater than one
    const double u(1.0+std::numeric_limits<float>::epsilon());
    if (rhs[0] < l || u < rhs[0] || rhs[1] < l || u < rhs[1]) {
        return false;
    }

    // compute points along line segments with minimal distance
    GeoLib::Point const p0(a[0]+rhs[0]*v[0], a[1]+rhs[0]*v[1], a[2]+rhs[0]*v[2]);
    GeoLib::Point const p1(c[0]+rhs[1]*w[0], c[1]+rhs[1]*w[1], c[2]+rhs[1]*w[2]);

    double const min_dist(sqrt(MathLib::sqrDist(p0, p1)));
    double const min_seg_len(std::min(sqrt(sqr_len_v), sqrt(sqr_len_w)));
    if (min_dist < min_seg_len * 1e-6) {
        s[0] = 0.5 * (p0[0] + p1[0]);
        s[1] = 0.5 * (p0[1] + p1[1]);
        s[2] = 0.5 * (p0[2] + p1[2]);
        return true;
    }

    return false;
}

bool lineSegmentsIntersect(const GeoLib::Polyline* ply,
                           GeoLib::Polyline::SegmentIterator &seg_it0,
                           GeoLib::Polyline::SegmentIterator &seg_it1,
                           GeoLib::Point& intersection_pnt)
{
    std::size_t const n_segs(ply->getNumberOfSegments());
    // Neighbouring segments always intersects at a common vertex. The algorithm
    // checks for intersections of non-neighbouring segments.
    for (seg_it0 = ply->begin(); seg_it0 != ply->end() - 2; ++seg_it0)
    {
        seg_it1 = seg_it0+2;
        std::size_t const seg_num_0 = seg_it0.getSegmentNumber();
        for ( ; seg_it1 != ply->end(); ++seg_it1) {
            // Do not check first and last segment, because they are
            // neighboured.
            if (!(seg_num_0 == 0 && seg_it1.getSegmentNumber() == n_segs - 1)) {
                if (lineSegmentIntersect(*seg_it0, *seg_it1, intersection_pnt)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isPointInTriangle(MathLib::Point3d const& p,
                       MathLib::Point3d const& a,
                       MathLib::Point3d const& b,
                       MathLib::Point3d const& c,
                       double eps_pnt_out_of_plane,
                       double eps_pnt_out_of_tri,
                       GeoLib::TriangleTest algorithm)
{
    switch (algorithm)
    {
    case GeoLib::GAUSS:
        return gaussPointInTriangle(p, a, b, c, eps_pnt_out_of_plane, eps_pnt_out_of_tri);
    case GeoLib::BARYCENTRIC:
        return barycentricPointInTriangle(p, a, b, c, eps_pnt_out_of_plane, eps_pnt_out_of_tri);
    default:
        ERR ("Selected algorithm for point in triangle testing not found, falling back on default.");
    }
    return gaussPointInTriangle(p, a, b, c, eps_pnt_out_of_plane, eps_pnt_out_of_tri);
}

bool gaussPointInTriangle(MathLib::Point3d const& q,
                          MathLib::Point3d const& a,
                          MathLib::Point3d const& b,
                          MathLib::Point3d const& c,
                          double eps_pnt_out_of_plane,
                          double eps_pnt_out_of_tri)
{
    MathLib::Vector3 const v(a, b);
    MathLib::Vector3 const w(a, c);

    MathLib::DenseMatrix<double> mat (2,2);
    mat(0,0) = v.getSqrLength();
    mat(0,1) = v[0]*w[0] + v[1]*w[1] + v[2]*w[2];
    mat(1,0) = mat(0,1);
    mat(1,1) = w.getSqrLength();
    double y[2] = {
        v[0] * (q[0] - a[0]) + v[1] * (q[1] - a[1]) + v[2] * (q[2] - a[2]),
        w[0] * (q[0] - a[0]) + w[1] * (q[1] - a[1]) + w[2] * (q[2] - a[2])
    };

    MathLib::GaussAlgorithm<MathLib::DenseMatrix<double>, double*> gauss;
    gauss.solve(mat, y);

    const double lower (eps_pnt_out_of_tri);
    const double upper (1 + lower);

    if (-lower <= y[0] && y[0] <= upper && -lower <= y[1] && y[1] <= upper && y[0] + y[1] <=
        upper) {
        MathLib::Point3d const q_projected(std::array<double,3>{{
            a[0] + y[0] * v[0] + y[1] * w[0],
            a[1] + y[0] * v[1] + y[1] * w[1],
            a[2] + y[0] * v[2] + y[1] * w[2]
        }});
        if (MathLib::sqrDist(q, q_projected) <= eps_pnt_out_of_plane)
            return true;
    }

    return false;
}

bool barycentricPointInTriangle(MathLib::Point3d const& p,
                                MathLib::Point3d const& a,
                                MathLib::Point3d const& b,
                                MathLib::Point3d const& c,
                                double eps_pnt_out_of_plane,
                                double eps_pnt_out_of_tri)
{
    if (std::abs(orientation3d(p, a, b, c)) > eps_pnt_out_of_plane)
        return false;

    MathLib::Vector3 const pa (p,a);
    MathLib::Vector3 const pb (p,b);
    MathLib::Vector3 const pc (p,c);
    double const area_x_2 (calcTriangleArea(a,b,c) * 2);

    double const alpha ((MathLib::crossProduct(pb,pc).getLength()) / area_x_2);
    if (alpha < -eps_pnt_out_of_tri || alpha > 1+eps_pnt_out_of_tri)
        return false;
    double const beta  ((MathLib::crossProduct(pc,pa).getLength()) / area_x_2);
    if (beta  < -eps_pnt_out_of_tri || beta  > 1+eps_pnt_out_of_tri)
        return false;
    double const gamma (1 - alpha - beta);
    if (gamma < -eps_pnt_out_of_tri || gamma > 1+eps_pnt_out_of_tri)
        return false;
    return true;
}

bool isPointInTetrahedron(MathLib::Point3d const& p,
    MathLib::Point3d const& a, MathLib::Point3d const& b,
    MathLib::Point3d const& c, MathLib::Point3d const& d, double eps)
{
    double const d0 (orientation3d(d,a,b,c));
    // if tetrahedron is not coplanar
    if (std::abs(d0) > std::numeric_limits<double>::epsilon())
    {
        bool const d0_sign (d0>0);
        // if p is on the same side of bcd as a
        double const d1 (orientation3d(d, p, b, c));
        if (!(d0_sign == (d1>=0) || std::abs(d1) < eps))
            return false;
        // if p is on the same side of acd as b
        double const d2 (orientation3d(d, a, p, c));
        if (!(d0_sign == (d2>=0) || std::abs(d2) < eps))
            return false;
        // if p is on the same side of abd as c
        double const d3 (orientation3d(d, a, b, p));
        if (!(d0_sign == (d3>=0) || std::abs(d3) < eps))
            return false;
        // if p is on the same side of abc as d
        double const d4 (orientation3d(p, a, b, c));
        if (!(d0_sign == (d4>=0) || std::abs(d4) < eps))
            return false;
        return true;
    }
    return false;
}

double calcTriangleArea(MathLib::Point3d const& a,
    MathLib::Point3d const& b, MathLib::Point3d const& c)
{
    MathLib::Vector3 const u(a,c);
    MathLib::Vector3 const v(a,b);
    MathLib::Vector3 const w(MathLib::crossProduct(u, v));
    return 0.5 * w.getLength();
}

double calcTetrahedronVolume(MathLib::Point3d const& x1,
    MathLib::Point3d const& x2,
    MathLib::Point3d const& x3,
    MathLib::Point3d const& x4)
{
    const MathLib::Vector3 ab(x1, x2);
    const MathLib::Vector3 ac(x1, x3);
    const MathLib::Vector3 ad(x1, x4);
    return std::abs(GeoLib::scalarTriple(ac, ad, ab)) / 6.0;
}

void computeRotationMatrixToXZ(MathLib::Vector3 const& plane_normal, MathLib::DenseMatrix<double> & rot_mat)
{
    // *** some frequently used terms ***
    // n_1^2 + n_2^2
    const double h0(plane_normal[0] * plane_normal[0] + plane_normal[1] * plane_normal[1]);
    // 1 / sqrt (n_1^2 + n_2^2)
    const double h1(1.0 / sqrt(h0));
    // 1 / sqrt (n_1^2 + n_2^2 + n_3^2)
    const double h2(1.0 / sqrt(h0 + plane_normal[2] * plane_normal[2]));

    // calc rotation matrix
    rot_mat(0, 0) = plane_normal[1] * h1;
    rot_mat(0, 1) = -plane_normal[0] * h1;
    rot_mat(0, 2) = 0.0;
    rot_mat(1, 0) = plane_normal[0] * h2;
    rot_mat(1, 1) = plane_normal[1] * h2;
    rot_mat(1, 2) = plane_normal[2] * h2;
    rot_mat(2, 0) = plane_normal[0] * plane_normal[2] * h1 * h2;
    rot_mat(2, 1) = plane_normal[1] * plane_normal[2] * h1 * h2;
    rot_mat(2, 2) = -sqrt(h0) * h2;
}

void rotatePoints(MathLib::DenseMatrix<double> const& rot_mat, std::vector<GeoLib::Point*> &pnts)
{
    rotatePoints(rot_mat, pnts.begin(), pnts.end());
}

MathLib::DenseMatrix<double> rotatePointsToXY(std::vector<GeoLib::Point*>& pnts)
{
    return rotatePointsToXY(pnts.begin(), pnts.end(), pnts.begin(), pnts.end());
}

void rotatePointsToXZ(std::vector<GeoLib::Point*> &pnts)
{
    assert(pnts.size()>2);
    // calculate supporting plane
    MathLib::Vector3 plane_normal;
    double d;
    // compute the plane normal
    GeoLib::getNewellPlane(pnts, plane_normal, d);

    const double tol (std::numeric_limits<double>::epsilon());
    if (std::abs(plane_normal[0]) > tol || std::abs(plane_normal[1]) > tol) {
        // rotate copied points into x-z-plane
        MathLib::DenseMatrix<double> rot_mat(3, 3);
        computeRotationMatrixToXZ(plane_normal, rot_mat);
        rotatePoints(rot_mat, pnts);
    }

    for (std::size_t k(0); k<pnts.size(); k++)
        (*(pnts[k]))[1] = 0.0; // should be -= d but there are numerical errors
}

std::unique_ptr<GeoLib::Point> triangleLineIntersection(
    MathLib::Point3d const& a, MathLib::Point3d const& b,
    MathLib::Point3d const& c, MathLib::Point3d const& p,
    MathLib::Point3d const& q)
{
    const MathLib::Vector3 pq(p, q);
    const MathLib::Vector3 pa(p, a);
    const MathLib::Vector3 pb(p, b);
    const MathLib::Vector3 pc(p, c);

    double u (scalarTriple(pq, pc, pb));
    if (u<0) return nullptr;
    double v (scalarTriple(pq, pa, pc));
    if (v<0) return nullptr;
    double w (scalarTriple(pq, pb, pa));
    if (w<0) return nullptr;

    const double denom (1.0/(u+v+w));
    u*=denom;
    v*=denom;
    w*=denom;
    return std::unique_ptr<GeoLib::Point>{
        new GeoLib::Point(u * a[0] + v * b[0] + w * c[0],
                          u * a[1] + v * b[1] + w * c[1],
                          u * a[2] + v * b[2] + w * c[2])};
}

double scalarTriple(MathLib::Vector3 const& u, MathLib::Vector3 const& v, MathLib::Vector3 const& w)
{
    MathLib::Vector3 const cross(MathLib::crossProduct(u, v));
    return MathLib::scalarProduct(cross,w);
}

double orientation3d(MathLib::Point3d const& p,
                     MathLib::Point3d const& a,
                     MathLib::Point3d const& b,
                     MathLib::Point3d const& c)
{
    MathLib::Vector3 const ap (a, p);
    MathLib::Vector3 const bp (b, p);
    MathLib::Vector3 const cp (c, p);
    return scalarTriple(bp,cp,ap);
}

bool dividedByPlane(const MathLib::Point3d& a, const MathLib::Point3d& b,
    const MathLib::Point3d& c, const MathLib::Point3d& d)
{
    for (unsigned x=0; x<3; ++x)
    {
        const unsigned y=(x+1)%3;
        const double abc = (b[x] - a[x])*(c[y] - a[y]) - (b[y] - a[y])*(c[x] - a[x]);
        const double abd = (b[x] - a[x])*(d[y] - a[y]) - (b[y] - a[y])*(d[x] - a[x]);

        if ((abc>0 && abd<0) || (abc<0 && abd>0))
            return true;
    }
    return false;
}

bool isCoplanar(const MathLib::Point3d& a, const MathLib::Point3d& b,
    const MathLib::Point3d& c, const MathLib::Point3d& d)
{
    const MathLib::Vector3 ab(a,b);
    const MathLib::Vector3 ac(a,c);
    const MathLib::Vector3 ad(a,d);

    if (ab.getSqrLength() < pow(std::numeric_limits<double>::epsilon(),2) ||
        ac.getSqrLength() < pow(std::numeric_limits<double>::epsilon(),2) ||
        ad.getSqrLength() < pow(std::numeric_limits<double>::epsilon(),2)) {
        return true;
    }

    // In exact arithmetic <ac*ad^T, ab> should be zero
    // if all four points are coplanar.
    const double sqr_scalar_triple(pow(MathLib::scalarProduct(MathLib::crossProduct(ac,ad), ab),2));
    // Due to evaluating the above numerically some cancellation or rounding
    // can occur. For this reason a normalisation factor is introduced.
    const double normalisation_factor =
        (ab.getSqrLength() * ac.getSqrLength() * ad.getSqrLength());

    // tolerance 1e-11 is choosen such that
    // a = (0,0,0), b=(1,0,0), c=(0,1,0) and d=(1,1,1e-6) are considered as coplanar
    // a = (0,0,0), b=(1,0,0), c=(0,1,0) and d=(1,1,1e-5) are considered as not coplanar
    return (sqr_scalar_triple/normalisation_factor < 1e-11);
}

void computeAndInsertAllIntersectionPoints(GeoLib::PointVec &pnt_vec,
    std::vector<GeoLib::Polyline*> & plys)
{
    auto computeSegmentIntersections = [&pnt_vec](GeoLib::Polyline& poly0,
                                                  GeoLib::Polyline& poly1)
    {
        for (auto seg0_it(poly0.begin()); seg0_it != poly0.end(); ++seg0_it)
        {
            for (auto seg1_it(poly1.begin()); seg1_it != poly1.end(); ++seg1_it)
            {
                GeoLib::Point s(0.0, 0.0, 0.0, pnt_vec.size());
                if (lineSegmentIntersect(*seg0_it, *seg1_it, s))
                {
                    std::size_t const id(
                        pnt_vec.push_back(new GeoLib::Point(s)));
                    poly0.insertPoint(seg0_it.getSegmentNumber() + 1, id);
                    poly1.insertPoint(seg1_it.getSegmentNumber() + 1, id);
                }
            }
        }
    };

    for (auto it0(plys.begin()); it0 != plys.end(); ++it0) {
        auto it1(it0);
        ++it1;
        for (; it1 != plys.end(); ++it1) {
            computeSegmentIntersections(*(*it0), *(*it1));
        }
    }
}

GeoLib::Polygon rotatePolygonToXY(GeoLib::Polygon const& polygon_in,
    MathLib::Vector3 & plane_normal)
{
    // 1 copy all points
    std::vector<GeoLib::Point*> *polygon_pnts(new std::vector<GeoLib::Point*>);
    for (std::size_t k(0); k < polygon_in.getNumberOfPoints(); k++)
        polygon_pnts->push_back (new GeoLib::Point (*(polygon_in.getPoint(k))));

    // 2 rotate points
    double d_polygon (0.0);
    GeoLib::getNewellPlane (*polygon_pnts, plane_normal, d_polygon);
    MathLib::DenseMatrix<double> rot_mat(3,3);
    GeoLib::computeRotationMatrixToXY(plane_normal, rot_mat);
    GeoLib::rotatePoints(rot_mat, *polygon_pnts);

    // 3 set z coord to zero
    std::for_each(polygon_pnts->begin(), polygon_pnts->end(),
        [] (GeoLib::Point* p) { (*p)[2] = 0.0; }
    );

    // 4 create new polygon
    GeoLib::Polyline rot_polyline(*polygon_pnts);
    for (std::size_t k(0); k < polygon_in.getNumberOfPoints(); k++)
        rot_polyline.addPoint(k);
    rot_polyline.addPoint(0);
    return GeoLib::Polygon(rot_polyline);
}

std::vector<MathLib::Point3d> lineSegmentIntersect2d(
    GeoLib::LineSegment const& ab, GeoLib::LineSegment const& cd)
{
    GeoLib::Point const& a{ab.getBeginPoint()};
    GeoLib::Point const& b{ab.getEndPoint()};
    GeoLib::Point const& c{cd.getBeginPoint()};
    GeoLib::Point const& d{cd.getEndPoint()};

    double const orient_abc(ExactPredicates::getOrientation2d(a, b, c));
    double const orient_abd(ExactPredicates::getOrientation2d(a, b, d));

    // check if the segment (cd) lies on the left or on the right of (ab)
    if ((orient_abc > 0 && orient_abd > 0) || (orient_abc < 0 && orient_abd < 0)) {
        return std::vector<MathLib::Point3d>();
    }

    // check: (cd) and (ab) are on the same line
    if (orient_abc == 0.0 && orient_abd == 0.0) {
        double const eps(std::numeric_limits<double>::epsilon());
        if (MathLib::sqrDist2d(a,c) < eps && MathLib::sqrDist2d(b,d) < eps)
            return {{ a, b }};
        if (MathLib::sqrDist2d(a,d) < eps && MathLib::sqrDist2d(b,c) < eps)
            return {{ a, b }};

        // Since orient_ab and orient_abd vanish, a, b, c, d are on the same
        // line and for this reason it is enough to check the x-component.
        auto isPointOnSegment = [](double q, double p0, double p1)
        {
            double const t((q - p0) / (p1 - p0));
            if (0 <= t && t <= 1) return true;
            return false;
        };

        // check if c in (ab)
        if (isPointOnSegment(c[0], a[0], b[0])) {
            // check if a in (cd)
            if (isPointOnSegment(a[0], c[0], d[0])) {
                return {{a, c}};
            }
            // check b == c
            if (MathLib::sqrDist2d(b,c) < eps) {
                return {{b}};
            }
            // check if b in (cd)
            if (isPointOnSegment(b[0], c[0], d[0])) {
                return {{b, c}};
            }
            // check d in (ab)
            if (isPointOnSegment(d[0], a[0], b[0])) {
                return {{c, d}};
            }
            std::stringstream err;
            err.precision(std::numeric_limits<double>::digits10);
            err << ab << " x " << cd;
            ERR(
                "The case of parallel line segments (%s) is not handled yet. "
                "Aborting.",
                err.str().c_str());
            std::abort();
        }

        // check if d in (ab)
        if (isPointOnSegment(d[0], a[0], b[0])) {
            // check if a in (cd)
            if (isPointOnSegment(a[0], c[0], d[0])) {
                return {{a, d}};
            }
            // check if b==d
            if (MathLib::sqrDist2d(b, d) < eps) {
                return {{b}};
            }
            // check if b in (cd)
            if (isPointOnSegment(b[0], c[0], d[0])) {
                return {{b, d}};
            }
            // d in (ab), b not in (cd): check c in (ab)
            if (isPointOnSegment(c[0], a[0], b[0])) {
                return {{c, d}};
            }

            std::stringstream err;
            err.precision(std::numeric_limits<double>::digits10);
            err << ab << " x " << cd;
            ERR(
                "The case of parallel line segments (%s) "
                "is not handled yet. Aborting.",
                err.str().c_str());
            std::abort();
        }
        return std::vector<MathLib::Point3d>();
    }

    auto isCollinearPointOntoLineSegment = [](MathLib::Point3d const& a,
        MathLib::Point3d const& b, MathLib::Point3d const& c)
        {
            double const t((c[0]-a[0])/(b[0]-a[0]));
            if (0.0 <= t && t <= 1.0)
                return true;
            return false;
        };

    if (orient_abc == 0.0) {
        if (isCollinearPointOntoLineSegment(a,b,c))
            return {{c}};
        return std::vector<MathLib::Point3d>();
    }

    if (orient_abd == 0.0) {
        if (isCollinearPointOntoLineSegment(a,b,d))
            return {{d}};
        return std::vector<MathLib::Point3d>();
    }

    // check if the segment (ab) lies on the left or on the right of (cd)
    double const orient_cda(ExactPredicates::getOrientation2d(c, d, a));
    double const orient_cdb(ExactPredicates::getOrientation2d(c, d, b));
    if ((orient_cda > 0 && orient_cdb > 0) || (orient_cda < 0 && orient_cdb < 0)) {
        return std::vector<MathLib::Point3d>();
    }

    // at this point it is sure that there is an intersection and the system of
    // linear equations will be invertible
    // solve the two linear equations (b-a, c-d) (t, s)^T = (c-a) simultaneously
    MathLib::DenseMatrix<double, std::size_t> mat(2,2);
    mat(0,0) = b[0]-a[0];
    mat(0,1) = c[0]-d[0];
    mat(1,0) = b[1]-a[1];
    mat(1,1) = c[1]-d[1];
    std::vector<double> rhs = {{c[0]-a[0], c[1]-a[1]}};

    MathLib::GaussAlgorithm<
        MathLib::DenseMatrix<double, std::size_t>, std::vector<double>> solver;
    solver.solve(mat, rhs);
    if (0 <= rhs[1] && rhs[1] <= 1.0) {
        return { MathLib::Point3d{std::array<double,3>{{
                c[0]+rhs[1]*(d[0]-c[0]), c[1]+rhs[1]*(d[1]-c[1]),
                c[2]+rhs[1]*(d[2]-c[2])}} } };
    } else {
        return std::vector<MathLib::Point3d>(); // parameter s not in the valid range
    }
}

void sortSegments(
    MathLib::Point3d const& seg_beg_pnt,
    std::vector<GeoLib::LineSegment>& sub_segments)
{
    double const eps(std::numeric_limits<double>::epsilon());

    auto findNextSegment = [&eps](
        MathLib::Point3d const& seg_beg_pnt,
        std::vector<GeoLib::LineSegment>& sub_segments,
        std::vector<GeoLib::LineSegment>::iterator& sub_seg_it)
    {
        if (sub_seg_it == sub_segments.end())
            return;
        // find appropriate segment for the given segment begin point
        auto act_beg_seg_it = std::find_if(
            sub_seg_it, sub_segments.end(),
            [&seg_beg_pnt, &eps](GeoLib::LineSegment const& seg)
            {
                return MathLib::sqrDist(seg_beg_pnt, seg.getBeginPoint()) < eps ||
                       MathLib::sqrDist(seg_beg_pnt, seg.getEndPoint()) < eps;
            });
        if (act_beg_seg_it == sub_segments.end())
            return;
        // if necessary correct orientation of segment, i.e. swap beg and end
        if (MathLib::sqrDist(seg_beg_pnt, act_beg_seg_it->getEndPoint()) <
            MathLib::sqrDist(seg_beg_pnt, act_beg_seg_it->getBeginPoint()))
            std::swap(act_beg_seg_it->getBeginPoint(),
                      act_beg_seg_it->getEndPoint());
        assert(sub_seg_it != sub_segments.end());
        // exchange segments within the container
        if (sub_seg_it != act_beg_seg_it)
            std::swap(*sub_seg_it, *act_beg_seg_it);
    };

    // find start segment
    auto seg_it = sub_segments.begin();
    findNextSegment(seg_beg_pnt, sub_segments, seg_it);

    while (seg_it != sub_segments.end())
    {
        MathLib::Point3d & new_seg_beg_pnt(seg_it->getEndPoint());
        seg_it++;
        if (seg_it != sub_segments.end())
            findNextSegment(new_seg_beg_pnt, sub_segments, seg_it);
    }
}

} // end namespace GeoLib
