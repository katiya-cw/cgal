#include <CGAL/Random.h>

//#define typename 

template <class SK>
void _test_circular_arc_point_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Sphere_3                          Sphere_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Construct_circular_arc_point_3   Construct_circular_arc_point_3;
  typedef typename SK::Construct_sphere_3               Construct_sphere_3;
  typedef typename SK::Equal_3                          Equal_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;
  
  Construct_sphere_3 theConstruct_sphere_3 = sk.construct_sphere_3_object();
  Construct_circular_arc_point_3 theConstruct_circular_arc_point_3 =
    sk.construct_circular_arc_point_3_object();
  Equal_3 theEqual_3 = sk.equal_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 127;
  int random_min = -127; 

  // test the constructor with 3 root_of_2
  Root_of_2 r1 = Root_of_2(3,-1,2);
  Root_of_2 r2 = Root_of_2(4,1,2);
  Root_of_2 r3 = Root_of_2(10,2,2);
  Root_for_spheres_2_3 rs = Root_for_spheres_2_3(r1,r2,r3);
  Circular_arc_point_3 circ_a_point_test_1 = 
    theConstruct_circular_arc_point_3(r1,r2,r3);
  Circular_arc_point_3 circ_a_point_test_4 = 
    theConstruct_circular_arc_point_3(rs);
  std::cout << "Testing Construct_circular_arc_point_3 with 3 Root_of_2..." << std::endl;
  assert(circ_a_point_test_1.x() == r1);
  assert(circ_a_point_test_1.y() == r2);
  assert(circ_a_point_test_1.z() == r3);

  std::cout << "Testing Construct_circular_arc_point_3 with a Root_for_spheres_2_3..." << std::endl;
  assert(circ_a_point_test_4.x() == r1);
  assert(circ_a_point_test_4.y() == r2);
  assert(circ_a_point_test_4.z() == r3);

  std::cout << "Testing many random cases of Construct_circular_arc_point_3..." << std::endl;
  for(int i=0; i<100; i++) {
    int a = theRandom.get_int(random_min,random_max);
    int b = theRandom.get_int(random_min,random_max);
    int c = theRandom.get_int(random_min,random_max);
    Circular_arc_point_3 circ_a_point_test_2 = 
      theConstruct_circular_arc_point_3(a,b,c);
    Circular_arc_point_3 circ_a_point_test_3 = 
      theConstruct_circular_arc_point_3(Point_3(a,b,c));
    assert(circ_a_point_test_2.x() == a);
    assert(circ_a_point_test_2.y() == b);
    assert(circ_a_point_test_2.z() == c);
    assert(circ_a_point_test_3.x() == a);
    assert(circ_a_point_test_3.y() == b);
    assert(circ_a_point_test_3.z() == c);
    assert(theEqual_3(circ_a_point_test_2, circ_a_point_test_3));
  }

  // No need to test the constructors based on intersection
  // _test_intersect_construct will test it

}

template <class SK>
void _test_sphere_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Sphere_3                         Sphere_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Get_equation                     Get_equation;
  typedef typename SK::Construct_sphere_3               Construct_sphere_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;

  Get_equation theGet_equation = sk.get_equation_object();
  Construct_sphere_3 theConstruct_sphere_3 = sk.construct_sphere_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 127;
  int random_min = -127; 

  std::cout << "Testing Construct_sphere_3 and Get_equation(Sphere_3)......" << std::endl;
  for(int i=0; i<100; i++) {
    int a,b,c,r;
    do {
      a = theRandom.get_int(random_min,random_max);
      b = theRandom.get_int(random_min,random_max);
      c = theRandom.get_int(random_min,random_max);
      r = theRandom.get_int(random_min,random_max);
    } while(r <= 0);
    Polynomial_for_spheres_2_3 p = theGet_equation(Sphere_3(Point_3(a,b,c),r));
    assert(p.a() == a);
    assert(p.b() == b);
    assert(p.c() == c);
    assert(p.r_sq() == r);
    Sphere_3 s = theConstruct_sphere_3(p);
    assert(s.center().x() == a);
    assert(s.center().y() == b);
    assert(s.center().z() == c);
    assert(s.squared_radius() == r);
  }

}

template <class SK>
void _test_plane_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Plane_3                          Plane_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Get_equation                     Get_equation;
  typedef typename SK::Construct_plane_3                Construct_plane_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;

  Get_equation theGet_equation = sk.get_equation_object();
  Construct_plane_3 theConstruct_plane_3 = sk.construct_plane_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 127;
  int random_min = -127; 

  std::cout << "Testing Construct_plane_3 and Get_equation(Plane_3)..." << std::endl;
  for(int i=0; i<100; i++) {
    int a,b,c,d;
    do {
      a = theRandom.get_int(random_min,random_max);
      b = theRandom.get_int(random_min,random_max);
      c = theRandom.get_int(random_min,random_max);
      d = theRandom.get_int(random_min,random_max);
    } while((a == 0) && (b == 0) && (c == 0));
    Polynomial_1_3 p = theGet_equation(Plane_3(a,b,c,d));
    assert(p.a() == a);
    assert(p.b() == b);
    assert(p.c() == c);
    assert(p.d() == d);
    Plane_3 plane = theConstruct_plane_3(p);
    assert(plane.a() == a);
    assert(plane.b() == b);
    assert(plane.c() == c);
    assert(plane.d() == d);
  }

}

template <class SK>
void _test_line_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Line_3                           Line_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Get_equation                     Get_equation;
  typedef typename SK::Construct_line_3                 Construct_line_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;

  Get_equation theGet_equation = sk.get_equation_object();
  Construct_line_3 theConstruct_line_3 = sk.construct_line_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 127;
  int random_min = -127; 

  std::cout << "Testing Construct_line_3 and Get_equation(Line_3)..." << std::endl;
  for(int i=0; i<100; i++) {
    int a,b,c,d,e,f;
    do {
      a = theRandom.get_int(random_min,random_max);
      b = theRandom.get_int(random_min,random_max);
      c = theRandom.get_int(random_min,random_max);
      d = theRandom.get_int(random_min,random_max);
      e = theRandom.get_int(random_min,random_max);
      f = theRandom.get_int(random_min,random_max);
    } while((a == d) && (b == e) && (c == f));
    Point_3 pb = Point_3(d,e,f);
    Point_3 pa = Point_3(a,b,c);
    Polynomials_for_line_3 p = theGet_equation(Line_3(pa,pb));
    Root_for_spheres_2_3 r1 = Root_for_spheres_2_3(pb.x(),pb.y(),pb.z());
    Root_for_spheres_2_3 r2 = Root_for_spheres_2_3(pa.x(),pa.y(),pa.z());
    assert(r1.is_on_line(p));
    assert(r2.is_on_line(p));
    Line_3 line = theConstruct_line_3(p);
    assert(line.to_vector().x() == (d-a));
    assert(line.to_vector().y() == (e-b));
    assert(line.to_vector().z() == (f-c)); 
  }

}

template <class SK>
void _test_circle_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Plane_3                          Plane_3;
  typedef typename SK::Circle_3                         Circle_3;
  typedef typename SK::Sphere_3                         Sphere_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Get_equation                     Get_equation;
  typedef typename SK::Equal_3                          Equal_3;
  typedef typename SK::Construct_circle_3               Construct_circle_3;
  typedef typename SK::Construct_sphere_3               Construct_sphere_3;
  typedef typename SK::Polynomials_for_circle_3         Polynomials_for_circle_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;

  Equal_3 theEqual_3 = sk.equal_3_object();
  Get_equation theGet_equation = sk.get_equation_object();
  Construct_circle_3 theConstruct_circle_3 = sk.construct_circle_3_object();
  Construct_sphere_3 theConstruct_sphere_3 = sk.construct_sphere_3_object();

  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  CGAL::Random theRandom(random_seed);
  int random_max = 127;
  int random_min = -127; 

  std::cout << "Testing Construct_circle_3 and Get_equation(Circle_3)..." << std::endl;
  for(int i=0; i<100; i++) {
    int a,b,c,d,u,v,r;
    FT x,y,z;
    do {
      a = theRandom.get_int(random_min,random_max);
      b = theRandom.get_int(random_min,random_max);
      c = theRandom.get_int(random_min,random_max);
      d = theRandom.get_int(random_min,random_max);
    } while((a == 0) && (b == 0) && (c == 0));
    u = theRandom.get_int(random_min,random_max);
    v = theRandom.get_int(random_min,random_max);
    do {
      r = theRandom.get_int(random_min,random_max);
    } while(r <= 0);
    if(a != 0) {
      x = FT(-(b*u + c*v + d),a);
      y = FT(u);
      z = FT(v);
    } else if(b != 0) {
      x = FT(u);
      y = FT(-(a*u + c*v + d),b);
      z = FT(v);
    } else {
      x = FT(u);
      y = FT(v);
      z = FT(-(a*u + b*v + d),c);
    } 
    const Plane_3 plane = Plane_3(a,b,c,d);
    const Plane_3 plane2 = Plane_3(2*a,2*b,2*c,2*d);
    const FT sqr = FT(r);
    const Point_3 p = Point_3(x,y,z);
    const Polynomials_for_circle_3 pfc = 
      std::make_pair(Polynomial_for_spheres_2_3(x,y,z,r),
                     Polynomial_1_3(a,b,c,d));
    Circle_3 circle3 = theConstruct_circle_3(pfc);
    Circle_3 circle = theConstruct_circle_3(p,sqr,plane);
    assert(circle.supporting_plane().a() == a);
    assert(circle.supporting_plane().b() == b);
    assert(circle.supporting_plane().c() == c);
    assert(circle.supporting_plane().d() == d);
    assert(circle.center().x() == x);
    assert(circle.center().y() == y);
    assert(circle.center().z() == z);
    assert(circle.squared_radius() == sqr);
    Circle_3 circle2 = theConstruct_circle_3(p,sqr,plane2);
    assert(theEqual_3(circle,circle2));
    assert(theEqual_3(circle,circle3));
    Polynomials_for_circle_3 pcircle = theGet_equation(circle);
    assert(pcircle.second.a() == a);
    assert(pcircle.second.b() == b);
    assert(pcircle.second.c() == c);
    assert(pcircle.second.d() == d);
    assert(pcircle.first.a() == x);
    assert(pcircle.first.b() == y);
    assert(pcircle.first.c() == z);
    assert(pcircle.first.r_sq() == sqr);
  }

  // No need to test the constructors based on intersection
  // _test_intersect_construct will test it
}

template <class SK>
void _test_intersection_construct(SK sk) {
  typedef typename SK::RT                               RT;
  typedef typename SK::FT                               FT;
  typedef typename SK::Root_of_2                        Root_of_2;
  typedef typename SK::Circular_arc_point_3             Circular_arc_point_3;
  typedef typename SK::Point_3                          Point_3;
  typedef typename SK::Line_3                           Line_3;
  typedef typename SK::Plane_3                          Plane_3;
  typedef typename SK::Sphere_3                         Sphere_3;
  typedef typename SK::Circle_3                         Circle_3;
  typedef typename SK::Algebraic_kernel                 AK;
  typedef typename SK::Get_equation                     Get_equation;
  typedef typename SK::Equal_3                          Equal_3;
  typedef typename SK::Has_on_3                         Has_on_3;
  typedef typename SK::Intersect_3                      Intersect_3;
  typedef typename SK::Construct_circle_3               Construct_circle_3;
  typedef typename SK::Construct_sphere_3               Construct_sphere_3;
  typedef typename SK::Construct_plane_3                Construct_plane_3;
  typedef typename SK::Construct_line_3                 Construct_line_3;
  typedef typename SK::Polynomials_for_circle_3         Polynomials_for_circle_3;
  typedef typename AK::Polynomial_for_spheres_2_3       Polynomial_for_spheres_2_3;
  typedef typename AK::Polynomial_1_3                   Polynomial_1_3;
  typedef typename AK::Polynomials_for_line_3           Polynomials_for_line_3;
  typedef typename AK::Root_for_spheres_2_3             Root_for_spheres_2_3;

  Has_on_3 theHas_on_3 = sk.has_on_3_object();
  Equal_3 theEqual_3 = sk.equal_3_object();
  Intersect_3 theIntersect_3 = sk.intersect_3_object();
  Get_equation theGet_equation = sk.get_equation_object();
  Construct_circle_3 theConstruct_circle_3 = sk.construct_circle_3_object();
  Construct_sphere_3 theConstruct_sphere_3 = sk.construct_sphere_3_object();
  Construct_plane_3 theConstruct_plane_3 = sk.construct_plane_3_object();
  Construct_line_3 theConstruct_line_3 = sk.construct_line_3_object();

  std::cout << "Testing intersection(Sphere,Sphere)..." << std::endl;
  Sphere_3 s = theConstruct_sphere_3(Polynomial_for_spheres_2_3(0,0,0,1));
  Sphere_3 s_t10 = theConstruct_sphere_3(Polynomial_for_spheres_2_3(10,10,10,1));
  for(int vx=-3;vx<4;vx++) {
    for(int vy=-3;vy<4;vy++) {
      for(int vz=-3;vz<4;vz++) {
        for(int vr=1;vr<6;vr++) {
          const FT x = FT(vx);
          const FT y = FT(vy);
          const FT z = FT(vz);
          const FT r = FT(vr,2);
          Sphere_3 sl_1 = theConstruct_sphere_3(
            Polynomial_for_spheres_2_3(x,y,z,r*r));
          Sphere_3 sl_2 = theConstruct_sphere_3(
            Polynomial_for_spheres_2_3(x+10,y+10,z+10,r*r));
          int d2 = (vx*vx + vy*vy + vz*vz);
          std::vector< CGAL::Object > intersection_1;
          std::vector< CGAL::Object > intersection_2;
          theIntersect_3(s, sl_1, std::back_inserter(intersection_1));
          theIntersect_3(s_t10, sl_2, std::back_inserter(intersection_2));
          // No intersection
          if((d2 > (r+1)*(r+1)) || (d2 < (r-1)*(r-1))) {
            assert(intersection_1.size() == 0);
            assert(intersection_2.size() == 0);
          } 
          // All the sphere intersect
          else if(x == 0 && y == 0 && z == 0 && r == 1) {
            assert(intersection_1.size() == 1);
            assert(intersection_2.size() == 1);
            Sphere_3 sphere1, sphere2;
            assert(assign(sphere1, intersection_1[0]));
            assert(assign(sphere2, intersection_2[0]));
          } 
          // Tangent, 1 Intersection
          else if((d2 == (r+1)*(r+1)) || (d2 == (r-1)*(r-1))) {
            assert(intersection_1.size() == 1);
            assert(intersection_2.size() == 1);
            std::pair<Circular_arc_point_3, unsigned > the_pair1;
            assert(assign(the_pair1, intersection_1[0]));
            std::pair<Circular_arc_point_3, unsigned > the_pair2;
            assert(assign(the_pair2, intersection_2[0]));
            assert(theHas_on_3(s,the_pair1.first));
            assert(theHas_on_3(sl_1,the_pair1.first));
            assert(theHas_on_3(s_t10,the_pair2.first));
            assert(theHas_on_3(sl_2,the_pair2.first));
          }
          // 1 Intersection Circle
          else {
            assert(intersection_1.size() == 1);
            assert(intersection_2.size() == 1);
            Circle_3 circle1, circle2;
            assert(assign(circle1, intersection_1[0]));
            assert(assign(circle2, intersection_2[0]));
            assert(theHas_on_3(s,circle1));
            assert(theHas_on_3(sl_1,circle1));
            assert(theHas_on_3(s_t10,circle2));
            assert(theHas_on_3(sl_2,circle2));
          }
        }
      }
    }
  }

  std::cout << "Testing intersection(Sphere,Plane)..." << std::endl;
  Plane_3 p = theConstruct_plane_3(Polynomial_1_3(1,1,1,-1));
  for(int vx=-2;vx<3;vx++) {
    for(int vy=-2;vy<3;vy++) {
      for(int vz=-2;vz<3;vz++) {
        for(int vr=1;vr<27;vr++) {
          const FT x = FT(vx);
          const FT y = FT(vy);
          const FT z = FT(vz);
          const FT sq_r = FT(vr,3);
          Sphere_3 sl = theConstruct_sphere_3(
            Polynomial_for_spheres_2_3(x,y,z,sq_r));
          const FT d2 = ((x+y+z-1)*(x+y+z-1) / 3);
          std::vector< CGAL::Object > intersection_1;
          theIntersect_3(p, sl, std::back_inserter(intersection_1));

          // No intersection
          if(d2 > sq_r) {
            assert(intersection_1.size() == 0);
          } 
          // Tangent, 1 Intersection
          else if(d2 == sq_r) {
            assert(intersection_1.size() == 1);
            std::pair<Circular_arc_point_3, unsigned > the_pair1;
            assert(assign(the_pair1, intersection_1[0]));
            assert(theHas_on_3(sl,the_pair1.first));
            assert(theHas_on_3(p,the_pair1.first));
          }
          // 1 Intersection Circle
          else {
            assert(intersection_1.size() == 1);
            Circle_3 circle1;
            assert(assign(circle1, intersection_1[0]));
            assert(theHas_on_3(sl,circle1));
            assert(theHas_on_3(p,circle1));
          }
        }
      }
    }
  }

  std::cout << "Testing intersection(Sphere,Line)..." << std::endl;
  for(int vx=-2;vx<3;vx++) {
    for(int vy=-2;vy<3;vy++) {
      for(int vz=-2;vz<3;vz++) {
        if(vx == -1 && vy == 0 && vz == 0) continue;
        const FT x = FT(vx);
        const FT y = FT(vy);
        const FT z = FT(vz);
        Line_3 l1 = theConstruct_line_3(Point_3(-1,0,0), Point_3(x,y,z));
        Line_3 l2 = theConstruct_line_3(Point_3(-1-FT(1,1000000),0,0), Point_3(x,y,z));
        std::vector< CGAL::Object > intersection_1, intersection_2;
        theIntersect_3(s, l1, std::back_inserter(intersection_1));
        theIntersect_3(s, l2, std::back_inserter(intersection_2));

        // tangent case for line 1
        // non-intersection for line 2
        if(vx == -1) {
          assert(intersection_1.size() == 1);
          std::pair<Circular_arc_point_3, unsigned > the_pair1;
          assert(assign(the_pair1, intersection_1[0]));
          assert(theHas_on_3(s,the_pair1.first));
          assert(theHas_on_3(l1,the_pair1.first));

          assert(intersection_2.size() == 0);
        }

        // 2 intersections for line 1
        // 2 intersections for line 2
        else {
          assert(intersection_1.size() == 2);
          std::pair<Circular_arc_point_3, unsigned > the_pair1;
          std::pair<Circular_arc_point_3, unsigned > the_pair2;
          assert(assign(the_pair1, intersection_1[0]));
          assert(assign(the_pair2, intersection_1[1]));
          assert(theHas_on_3(s,the_pair1.first));
          assert(theHas_on_3(l1,the_pair1.first));
          assert(theHas_on_3(s,the_pair2.first));
          assert(theHas_on_3(l1,the_pair2.first));

          assert(intersection_2.size() == 2);
          std::pair<Circular_arc_point_3, unsigned > the_pair3;
          std::pair<Circular_arc_point_3, unsigned > the_pair4;
          assert(assign(the_pair3, intersection_2[0]));
          assert(assign(the_pair4, intersection_2[1]));
          assert(theHas_on_3(s,the_pair3.first));
          assert(theHas_on_3(l2,the_pair3.first));
          assert(theHas_on_3(s,the_pair4.first));
          assert(theHas_on_3(l2,the_pair4.first));
        }

      }
    }
  }

  std::cout << "Testing intersection(Sphere,Sphere,Sphere)..." << std::endl;
  Sphere_3 s1 = theConstruct_sphere_3(Polynomial_for_spheres_2_3(0,0,0,16));
  Sphere_3 s2 = theConstruct_sphere_3(Polynomial_for_spheres_2_3(4,0,0,16));
  Sphere_3 s3 = theConstruct_sphere_3(Polynomial_for_spheres_2_3(8,0,0,16));
  for(int vx=-1;vx<5;vx++) {
    for(int vy=-1;vy<5;vy++) {
      for(int vz=-1;vz<5;vz++) {
        for(int vr=1;vr<6;vr++) {
          const FT x = 4*FT(vx);
          const FT y = 4*FT(vy);
          const FT z = 4*FT(vz);
          const FT r = 4*FT(vr,2);
          Sphere_3 sl = theConstruct_sphere_3(
            Polynomial_for_spheres_2_3(x,y,z,r*r));
          std::vector< CGAL::Object > intersection_1;
          std::vector< CGAL::Object > intersection_2;
          theIntersect_3(s1, s2, sl, std::back_inserter(intersection_1));
          theIntersect_3(s1, s3, sl, std::back_inserter(intersection_2));
          if(intersection_1.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_1[0])) {
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(s2,circle));
              assert(theHas_on_3(sl,circle));
            }
            if(assign(cap,intersection_1[0])) {
              // This case must never happen
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(s2,cap.first));
              assert(theHas_on_3(sl,cap.first));
            }
          }
          if(intersection_1.size() == 2) {
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_1[0]));
            assert(assign(cap2,intersection_1[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(s2,cap1.first));
            assert(theHas_on_3(sl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(s2,cap2.first));
            assert(theHas_on_3(sl,cap2.first));
          }

          if(intersection_2.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_2[0])) {
              // This case must never happen
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(s3,circle));
              assert(theHas_on_3(sl,circle));
            }
            if(assign(cap,intersection_2[0])) {
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(s3,cap.first));
              assert(theHas_on_3(sl,cap.first));
            }
          }
          if(intersection_2.size() == 2) {
            // This case must never happen
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_2[0]));
            assert(assign(cap2,intersection_2[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(s3,cap1.first));
            assert(theHas_on_3(sl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(s3,cap2.first));
            assert(theHas_on_3(sl,cap2.first));
          }
        }
      }
    }
  }

  std::cout << "Testing intersection(Sphere,Sphere,Plane)..." << std::endl;
  for(int va=-1;va<3;va++) {
    for(int vb=-1;vb<3;vb++) {
      for(int vc=-1;vc<3;vc++) {
        for(int vd=-8;vd<9;vd++) {
          const FT a = FT(va);
          const FT b = FT(vb);
          const FT c = FT(vc);
          const FT d = -FT(vd,2);
          if(a == 0 && b == 0 && c == 0) continue;
          Plane_3 pl = theConstruct_plane_3(
            Polynomial_1_3(a,b,c,d));
          std::vector< CGAL::Object > intersection_1;
          std::vector< CGAL::Object > intersection_2;
          theIntersect_3(s1, s2, pl, std::back_inserter(intersection_1));
          theIntersect_3(s1, s3, pl, std::back_inserter(intersection_2));
          if(intersection_1.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_1[0])) {
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(s2,circle));
              assert(theHas_on_3(pl,circle));
            }
            if(assign(cap,intersection_1[0])) {
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(s2,cap.first));
              assert(theHas_on_3(pl,cap.first));
            }
          }
          if(intersection_1.size() == 2) {
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_1[0]));
            assert(assign(cap2,intersection_1[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(s2,cap1.first));
            assert(theHas_on_3(pl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(s2,cap2.first));
            assert(theHas_on_3(pl,cap2.first));
          }
          if(intersection_2.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_2[0])) {
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(s3,circle));
              assert(theHas_on_3(pl,circle));
            }
            if(assign(cap,intersection_2[0])) {
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(s3,cap.first));
              assert(theHas_on_3(pl,cap.first));
            }
          }
          if(intersection_2.size() == 2) {
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_2[0]));
            assert(assign(cap2,intersection_2[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(s3,cap1.first));
            assert(theHas_on_3(pl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(s3,cap2.first));
            assert(theHas_on_3(pl,cap2.first));
          }
        }
      }
    }
  }

  // This test becomes almost Line vs Sphere, is not that interesting to test
  Plane_3 p1 = theConstruct_plane_3(Polynomial_1_3(1,1,1,0));
  Plane_3 p2 = theConstruct_plane_3(Polynomial_1_3(1,0,0,-4));
  std::cout << "Testing intersection(Plane,Plane,Sphere)..." << std::endl;
  for(int va=-1;va<3;va++) {
    for(int vb=-1;vb<3;vb++) {
      for(int vc=-1;vc<3;vc++) {
        for(int vd=-8;vd<9;vd++) {
          const FT a = FT(va);
          const FT b = FT(vb);
          const FT c = FT(vc);
          const FT d = -FT(vd,2);
          if(a == 0 && b == 0 && c == 0) continue;
          Plane_3 pl = theConstruct_plane_3(
            Polynomial_1_3(a,b,c,d));
          std::vector< CGAL::Object > intersection_1;
          std::vector< CGAL::Object > intersection_2;
          theIntersect_3(s1, p1, pl, std::back_inserter(intersection_1));
          theIntersect_3(s1, p2, pl, std::back_inserter(intersection_2));
          if(intersection_1.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_1[0])) {
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(p1,circle)); 
              assert(theHas_on_3(pl,circle));
            }
            if(assign(cap,intersection_1[0])) {
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(p1,cap.first));
              assert(theHas_on_3(pl,cap.first));
            }
          }
          if(intersection_1.size() == 2) {
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_1[0]));
            assert(assign(cap2,intersection_1[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(p1,cap1.first));
            assert(theHas_on_3(pl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(p1,cap2.first));
            assert(theHas_on_3(pl,cap2.first));
          }
          if(intersection_2.size() == 1) {
            Circle_3 circle;
            std::pair<Circular_arc_point_3, unsigned> cap;
            if(assign(circle,intersection_2[0])) {
              assert(theHas_on_3(s1,circle));
              assert(theHas_on_3(p2,circle));
              assert(theHas_on_3(pl,circle));
            }
            if(assign(cap,intersection_2[0])) {
              assert(theHas_on_3(s1,cap.first));
              assert(theHas_on_3(p2,cap.first));
              assert(theHas_on_3(pl,cap.first));
            }
          }
          if(intersection_2.size() == 2) {
            std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
            assert(assign(cap1,intersection_2[0]));
            assert(assign(cap2,intersection_2[1]));
            assert(theHas_on_3(s1,cap1.first));
            assert(theHas_on_3(p2,cap1.first));
            assert(theHas_on_3(pl,cap1.first));
            assert(theHas_on_3(s1,cap2.first));
            assert(theHas_on_3(p2,cap2.first));
            assert(theHas_on_3(pl,cap2.first));
          }
        }
      }
    }
  }

  std::cout << "Testing intersection(Circle,Sphere)..." << std::endl;
  std::cout << "Testing intersection(Circle,Plane)..." << std::endl;
  // both tests above are equivalent respectively to 
  // intersection(Sphere,Sphere,Plane) and
  // intersection(Plane,Plane,Sphere)*/

  std::cout << "Testing intersection(Circle,Circle)..." << std::endl;
  Polynomial_for_spheres_2_3 es1 = Polynomial_for_spheres_2_3(0,0,0,1);
  Polynomial_for_spheres_2_3 es2 = Polynomial_for_spheres_2_3(1,0,0,1);
  Polynomial_for_spheres_2_3 es3 = Polynomial_for_spheres_2_3(2,0,0,1);
  for(int va=-5;va<6;va++) {
    const FT a = -FT(va,10);
    const FT b = 1;
    const FT c = 0;
    const FT d = 0;
    Polynomial_1_3 pol = Polynomial_1_3(a,b,c,d);
    Circle_3 c1 = theConstruct_circle_3(std::make_pair(es1, pol));
    Circle_3 c2 = theConstruct_circle_3(std::make_pair(es2, pol));
    Circle_3 c3 = theConstruct_circle_3(std::make_pair(es3, pol));

    std::vector< CGAL::Object > intersection_1;
    theIntersect_3(c1, c1, std::back_inserter(intersection_1));
    assert(intersection_1.size() == 1);
    Circle_3 circle;
    assert(assign(circle,intersection_1[0]));
    assert(circle == c1);

    std::vector< CGAL::Object > intersection_2;
    theIntersect_3(c1, c2, std::back_inserter(intersection_2));
    assert(intersection_2.size() == 2);
    std::pair<Circular_arc_point_3, unsigned> cap1, cap2;
    assert(assign(cap1,intersection_2[0]));
    assert(assign(cap2,intersection_2[1]));
    assert(theHas_on_3(c1,cap1.first));
    assert(theHas_on_3(c2,cap1.first));
    assert(theHas_on_3(c1,cap2.first));
    assert(theHas_on_3(c2,cap2.first));

    std::vector< CGAL::Object > intersection_3;
    theIntersect_3(c1, c3, std::back_inserter(intersection_3));
    if(a != 0) {
      assert(intersection_3.size() == 0);
    } else {
      assert(intersection_3.size() == 1);
      std::pair<Circular_arc_point_3, unsigned> cap;
      assert(assign(cap,intersection_3[0]));
      assert(theHas_on_3(c1,cap.first));
      assert(theHas_on_3(c3,cap.first)); 
    }

    for(int vb=-5;vb<6;vb++) {
      const FT al = 1;
      const FT bl = 0;
      const FT cl = -FT(vb,10);
      const FT dl = 0;
      Polynomial_1_3 pol2 = Polynomial_1_3(al,bl,cl,dl);
      Circle_3 c4 = theConstruct_circle_3(std::make_pair(es1, pol2));
      std::vector< CGAL::Object > intersection_4;
      theIntersect_3(c1, c4, std::back_inserter(intersection_4));
      assert(intersection_4.size() == 2);
      assert(assign(cap1,intersection_4[0]));
      assert(assign(cap2,intersection_4[1]));
      assert(theHas_on_3(c1,cap1.first));
      assert(theHas_on_3(c4,cap1.first));
      assert(theHas_on_3(c1,cap2.first));
      assert(theHas_on_3(c4,cap2.first));
    }

    const FT a_c = FT(va,10);
    const FT b_c = 1;
    const FT c_c = 0;
    const FT d_c = -FT(va,10);
    Polynomial_1_3 pol2 = Polynomial_1_3(a_c,b_c,c_c,d_c);
    Circle_3 c5 = theConstruct_circle_3(std::make_pair(es2, pol2));
    std::vector< CGAL::Object > intersection_5;
    theIntersect_3(c1, c5, std::back_inserter(intersection_5));
    assert(intersection_5.size() == 2);
    assert(assign(cap1,intersection_5[0]));
    assert(assign(cap2,intersection_5[1]));
    assert(theHas_on_3(c1,cap1.first));
    assert(theHas_on_3(c5,cap1.first));
    assert(theHas_on_3(c1,cap2.first));
    assert(theHas_on_3(c5,cap2.first));

  }

  std::cout << "Testing intersection(Circle,Line)..." << std::endl;
  Polynomial_for_spheres_2_3 pol_s = Polynomial_for_spheres_2_3(0,0,0,1);
  for(int vx=-2;vx<3;vx++) {
    for(int vy=-2;vy<3;vy++) {
      for(int vz=-2;vz<3;vz++) {
        if(vx == -1 && vy == 0 && vz == 0) continue;
        const FT x = FT(vx);
        const FT y = FT(vy);
        const FT z = FT(vz);
        Line_3 l1 = theConstruct_line_3(Point_3(-1,0,0), Point_3(x,y,z));
        Plane_3 pl1 = theConstruct_plane_3(Point_3(-1,0,0), Point_3(x,y,z), 
                                           Point_3(3,4,5));
        Line_3 l2 = theConstruct_line_3(Point_3(-1-FT(1,1000000),0,0), 
                                        Point_3(x,y,z));
        Plane_3 pl2 = theConstruct_plane_3(Point_3(-1-FT(1,1000000),0,0), 
                                           Point_3(x,y,z), Point_3(3,4,5));
        Polynomial_1_3 pol_pl1 = theGet_equation(pl1);
        Polynomial_1_3 pol_pl2 = theGet_equation(pl2);
        Circle_3 c1 = theConstruct_circle_3(std::make_pair(pol_s, pol_pl1));
        Circle_3 c2 = theConstruct_circle_3(std::make_pair(pol_s, pol_pl2));

        std::vector< CGAL::Object > intersection_1, intersection_2;
        theIntersect_3(c1, l1, std::back_inserter(intersection_1));
        theIntersect_3(c2, l2, std::back_inserter(intersection_2));

        // tangent case for line 1
        // non-intersection for line 2
        if(vx == -1) {
          assert(intersection_1.size() == 1);
          std::pair<Circular_arc_point_3, unsigned > the_pair1;
          assert(assign(the_pair1, intersection_1[0]));
          assert(theHas_on_3(c1,the_pair1.first));
          assert(theHas_on_3(l1,the_pair1.first));

          assert(intersection_2.size() == 0);
        }

        // 2 intersections for line 1
        // 2 intersections for line 2
        else {
          assert(intersection_1.size() == 2);
          std::pair<Circular_arc_point_3, unsigned > the_pair1;
          std::pair<Circular_arc_point_3, unsigned > the_pair2;
          assert(assign(the_pair1, intersection_1[0]));
          assert(assign(the_pair2, intersection_1[1]));
          assert(theHas_on_3(c1,the_pair1.first));
          assert(theHas_on_3(l1,the_pair1.first));
          assert(theHas_on_3(c1,the_pair2.first));
          assert(theHas_on_3(l1,the_pair2.first));

          assert(intersection_2.size() == 2);
          std::pair<Circular_arc_point_3, unsigned > the_pair3;
          std::pair<Circular_arc_point_3, unsigned > the_pair4;
          assert(assign(the_pair3, intersection_2[0]));
          assert(assign(the_pair4, intersection_2[1]));
          assert(theHas_on_3(c2,the_pair3.first));
          assert(theHas_on_3(l2,the_pair3.first));
          assert(theHas_on_3(c2,the_pair4.first));
          assert(theHas_on_3(l2,the_pair4.first));
        }

      }
    }
  }
}

template <class SK>
void _test_spherical_kernel_construct(SK sk)
{
  std::cout << "TESTING CONSTRUCTIONS" << std::endl;
  _test_circular_arc_point_construct(sk);
  _test_sphere_construct(sk);
  _test_plane_construct(sk);
  _test_line_construct(sk);
  _test_circle_construct(sk);
  _test_intersection_construct(sk);
  std::cout << "All tests on construction are OK." << std::endl;
}
