// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Eric Berberich <eric@mpi-inf.mpg.de>
//                 Pavel Emeliyanenko <asm@mpi-sb.mpg.de>
//
// ============================================================================

#ifndef CGAL_CURVED_KERNEL_VIA_ANALYSIS_2L_FUNCTORS_H
#define CGAL_CURVED_KERNEL_VIA_ANALYSIS_2L_FUNCTORS_H

/*! \file Curved_kernel_via_analysis_2l_functors.h
 *  \brief Conatins functors for \c Curved_kernel_via_analysis_2l
 *  
 *  Functors for generic points and arcs on surfaces, lifted from 2D.
 */

#include <CGAL/basic.h>

#include <CGAL/Curved_kernel_via_analysis_2/Curved_kernel_via_analysis_2_functors.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

namespace Curved_kernel_via_analysis_2l_Functors {

#define CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES \
    typedef typename Base::Curve_2 Curve_2; \
    typedef typename Base::Point_2 Point_2; \
    typedef typename Base::Arc_2 Arc_2; \
    typedef typename Base::X_coordinate_1 X_coordinate_1; \


template < class CurvedKernelViaAnalysis_2l >
class Construct_point_2l : public Curved_kernel_via_analysis_2_Functors::
Curved_kernel_via_analysis_2_functor_base< CurvedKernelViaAnalysis_2l > {

public:
    //! this instance' first template parameter
    typedef CurvedKernelViaAnalysis_2l Curved_kernel_via_analysis_2l;

    //! the base type
    typedef 
    Curved_kernel_via_analysis_2_Functors::
    Curved_kernel_via_analysis_2_functor_base< Curved_kernel_via_analysis_2l >
    Base;
    
    CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES;
    
    //! type of projected point
    typedef typename Point_2::Projected_point_2 Projected_point_2;
    
    //! type of surface
    typedef typename Point_2::Surface_3 Surface_3;

    //! the result type
    typedef Point_2 result_type;
    
    //! standard constructor
    Construct_point_2l(Curved_kernel_via_analysis_2l *kernel) :
        Base(kernel) {
    }
    
    Point_2 operator()(const Projected_point_2& xy, 
                       const Surface_3& surface,
                       int sheet) const {
        CGAL_precondition(sheet >= 0);
        Point_2 pt(this->_ckva(), xy, surface, sheet);
        return pt;
    }
};

//!\brief Functor to construct point on an arc
//! \c x on curve \c c with arc number \c arcno
//!
//! implies no boundary conditions in x/y
template < class CurvedKernelViaAnalysis_2l >
class Construct_point_on_arc_2 : public Curved_kernel_via_analysis_2_Functors::
Curved_kernel_via_analysis_2_functor_base< CurvedKernelViaAnalysis_2l > {

public:
    //! this instance' first template parameter
    typedef CurvedKernelViaAnalysis_2l Curved_kernel_via_analysis_2l;

    //! the base type
    typedef 
    Curved_kernel_via_analysis_2_Functors::
    Curved_kernel_via_analysis_2_functor_base< Curved_kernel_via_analysis_2l >
    Base;
    
    CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES;
    
    //! the result type
    typedef Point_2 result_type;
    
    //! standard constructor
    Construct_point_on_arc_2(Curved_kernel_via_analysis_2l *kernel) :
        Base(kernel) {
    }
    
    //! constructs points at x 
    Point_2 operator()(
            const typename Point_2::X_coordinate_1& x, 
            const typename Point_2::Curve_2& c, int arcno,
            const Arc_2& arc) {
        CGAL_assertion(c.id() == arc.curve().id());
        CGAL_assertion(arcno == arc.arcno(x));
        typename Curved_kernel_via_analysis_2l::Construct_projected_point_2 
            construct_projected_point = 
            this->_ckva()->construct_projected_point_2_object();
        typename Point_2::Projected_point_2 p_pt = 
            construct_projected_point(x, c, arcno);
        int sheet = arc.sheet();
        if (arc.is_finite(CGAL::ARR_MIN_END)) {
            if (p_pt.compare_xy(
                        arc.curve_end(CGAL::ARR_MIN_END).projected_point()
                ) == CGAL::EQUAL) {
                sheet = arc.sheet(CGAL::ARR_MIN_END);
            }
        } else if (arc.is_finite(CGAL::ARR_MAX_END)) {
            if (p_pt.compare_xy(
                        arc.curve_end(CGAL::ARR_MAX_END).projected_point()
                ) == CGAL::EQUAL) {
                sheet = arc.sheet(CGAL::ARR_MAX_END);
            }
        }
        typename Curved_kernel_via_analysis_2l::Construct_point_2 
            construct_point_2 = this->_ckva()->construct_point_2_object();
        
        Point_2 pt = construct_point_2(p_pt, arc.surface(), sheet);
        return pt;
    }
};


template < class CurvedKernelViaAnalysis_2l >
class Construct_arc_2l : public Curved_kernel_via_analysis_2_Functors::
Curved_kernel_via_analysis_2_functor_base< CurvedKernelViaAnalysis_2l > {

public:
    //! this instance' first template parameter
    typedef CurvedKernelViaAnalysis_2l Curved_kernel_via_analysis_2l;

    //! the base type
    typedef 
    Curved_kernel_via_analysis_2_Functors::
    Curved_kernel_via_analysis_2_functor_base< Curved_kernel_via_analysis_2l >
    Base;
    
    CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES;
    
    //! type of point on surface
    typedef typename Curved_kernel_via_analysis_2l::Point_2 Surface_point_2l;
    
    //! type of arc on surface
    typedef typename Curved_kernel_via_analysis_2l::Arc_2 Surface_arc_2l;
    
    //! type of projected point
    typedef typename Surface_point_2l::Projected_point_2 Projected_point_2;
    
    //! type of projceteda rc
    typedef typename Surface_arc_2l::Projected_arc_2 Projected_arc_2;

    //! type of surface
    typedef typename Surface_point_2l::Surface_3 Surface_3;

    //! the result type
    typedef Point_2 result_type;
     
    //! standard constructor
    Construct_arc_2l(Curved_kernel_via_analysis_2l *kernel) :
        Base(kernel) {
    }
    
    //!\name Constructing non-vertical arcs
    //!@{
    
    /*!\brief
     * Standard constructor for an bounded arc on xy-monotone part
     * of the surface.
     * It represents the arc on \c surface covertical to \c arc which
     * lies on \c sheet of the xy-monotone subsurface.
     *
     * \pre arc.curve_end(MIN) = p
     * \pre arc.curve_end(MAX) = q
     */
    Surface_arc_2l operator()(const Projected_arc_2& arc, 
                              const Surface_point_2l& p,
                              const Surface_point_2l& q,
                              const Surface_3& surface,
                              int sheet, int sheet_p, int sheet_q) {
        Surface_arc_2l surface_arc(this->_ckva(), arc, p, q, surface, 
                                   sheet, sheet_p, sheet_q);
        return surface_arc;
    }
    
    /*!\brief
     * Standard constructor for a ray on xy-monotone part
     * of the surface.
     * It represents the arc on \c surface covertical to \c arc which
     * lies on \c sheet of the xy-monotone subsurface.
     *
     * \pre arc.curve_end(MIN) = p && !arc.is_finite(MAX) ||
     *      arc.is_finite(MIN) && arc.curve_end(MAX) = p
     */
    Surface_arc_2l operator()(const Projected_arc_2& arc, 
                              const Surface_point_2l& p,
                              const Surface_3& surface,
                              int sheet, int sheet_p) {
        // TODO precondition (eriC)
        CGAL_precondition(!arc.is_finite(CGAL::ARR_MIN_END) ||
                          !arc.is_finite(CGAL::ARR_MAX_END));
        Surface_arc_2l surface_arc(this->_ckva(), 
                                   arc, p, surface, sheet, sheet_p);
        return surface_arc;
    }
    

    /*!\brief
     * Standard constructor for a branch on xy-monotone part
     * of the surface.
     * It represents the arc on \c surface covertical to \c arc which
     * lies on \c sheet of the xy-monotone subsurface.
     *
     * \pre !arc.is_finite(MIN) && !arc.is_finite(MAX)
     */
    Surface_arc_2l operator()(const Projected_arc_2& arc, 
                   const Surface_3& surface,
                   int sheet) {
        CGAL_precondition(!arc.is_finite(CGAL::ARR_MIN_END));
        CGAL_precondition(!arc.is_finite(CGAL::ARR_MAX_END));
        Surface_arc_2l surface_arc(this->_ckva(), arc, surface, sheet);
        return surface_arc;
    }
    
    //!@}

    //!\name Constructing vertical arcs
    //!@{
    
    //! represents a bounded vertical arc
    Surface_arc_2l operator()(const Surface_point_2l& p,
                              const Surface_point_2l& q,
                              const Surface_3& surface) {
        Surface_arc_2l surface_arc(this->_ckva(), p, q, surface);
        return surface_arc;
    }

    //! represents a vertical ray
    Surface_arc_2l operator()(const Surface_point_2l p,
                              CGAL::Arr_curve_end inf_end,
                              const Surface_3& surface) {
        Surface_arc_2l surface_arc(this->_ckva(), p, inf_end, surface);
        return surface_arc;
    }

    //! represents a vertical branch
    Surface_arc_2l operator()(const Projected_point_2& p,
                              const Surface_3& surface) {
        Surface_arc_2l surface_arc(this->_ckva(), p, surface);
        return surface_arc;
    }
};


//!\brief Tests whether a point lies on a supporting curve
template < class CurvedKernelViaAnalysis_2l >
class Is_on_2: public Curved_kernel_via_analysis_2_Functors::
Curved_kernel_via_analysis_2_functor_base< CurvedKernelViaAnalysis_2l > {

public:
    //! this instance' first template parameter
    typedef CurvedKernelViaAnalysis_2l Curved_kernel_via_analysis_2l;

    //! the base type
    typedef 
    Curved_kernel_via_analysis_2_Functors::
    Curved_kernel_via_analysis_2_functor_base< Curved_kernel_via_analysis_2l >
    Base;
    
    CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES;
    
    //! the result type
    typedef bool result_type;
    typedef Arity_tag<2> Arity;
    
    //! standard constructor
    Is_on_2(Curved_kernel_via_analysis_2l *kernel) :
        Base(kernel) {
    }
    
    /*!
     * Checks whether \c p lies on \c c 
     * \param p1 The point to test
     * \param p2 The curve
     * \return (true) if the \c p lies on \c c
     */
    result_type operator()(const Point_2& p, const Curve_2& c) const {
        result_type res = false;
        // TODO implement Is_on_2 with Curve_2 == Surface_3 (eriC)
        CGAL_error_msg("Is_on_2 not implemented for Surfaces");
        return res;
    }
};

#undef CGAL_CKvA_2l_GRAB_BASE_FUNCTOR_TYPES 

} //  Curved_kernel_via_analysis_2l_Functors

} // namespace CGALi
 
CGAL_END_NAMESPACE

#endif // CGAL_CURVED_KERNEL_VIA_ANALYSIS_2L_FUNCTORS_H
// EOF
