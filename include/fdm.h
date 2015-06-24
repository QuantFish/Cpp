#ifndef FDM_H
#define FDM_H

#include "pde.h"
#include <vector>

// Finite Diffrence Method - Abstract Base Class
class FDMBase {
    public:
        // Carry out the actual time-stepping
        virtual void step_march() = 0;

    protected:
        ConvectionDiffusionPDE* pde;

        // Space discretisation
        double x_dom;  // Spatial extent [0.0, x_dom]
        unsigned long J; // Number of spatial diffrencing points
        double dx;  // Spatial step size (calculate from above)
        std::vector<double> x_values; // Stores the coordinates of the x dimention

        // Time discretisation
        double t_dom; // Temporal extent [0.0, t_dom]
        unsigned long N; // Number of temporal diffrencing points
        double dt;  // Temporal step size (calculated from above)

        // Time-marching
        double prev_t, cur_t; // Previous times and current times

        // Differencing coefficients
        double alpha, beta, gamma;

        // Storage
        std::vector<double> new_result; // New solution (become N+1)
        std::vector<double> old_result; // Old solution (bocome N)

        // Constructor

        FDMBase(double _x_dom, unsigned long _J, double _t_dom,
                unsigned long _N, ConvectionDiffusionPDE* _pde);


        // Overrides these virtual methods in derived classes for
        // specific FDM techniques, such as explicit Euler, Crank-Nicolson, etc.
        virtual void calculate_step_sizes() = 0;
        virtual void set_initial_conditions() = 0;
        virtual void calculate_boundary_conditions() = 0;
        virtual void calculate_inner_domain() = 0;

};

class FDMEulerExplicit: public FDMBase {
    protected:
        void calculate_step_sizes();
        void set_initial_conditions();
        void calculate_boundary_conditions();
        void calculate_inner_domain();

    public:
        FDMEulerExplicit(double _x_dom, unsigned long _J,
                         double _t_dom, unsigned long _N,
                         ConvectionDiffusionPDE* _pde);

        void step_march();
};

#endif // FDM_H