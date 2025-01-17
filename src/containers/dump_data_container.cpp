#include "containers/dump_data_container.h"

// Default constructor
dump_data_container::dump_data_container()
    : timestep_vec{}, atomscount_vec{}, frame_atoms_vec{}, frame_box_bounds_vec{}, max_boxbounds(3)
{
}

dump_data_container::dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec,
                                         std::vector<std::vector<std::unique_ptr<atom>>> fa_vec, std::vector<std::vector<std::pair<double, double>>> f_bb_vec)
    : timestep_vec(t_vec), atomscount_vec(ac_vec), frame_atoms_vec(std::move(fa_vec)), frame_box_bounds_vec(f_bb_vec), max_boxbounds(3)
{
}

std::vector<double> &dump_data_container::get_timestep_vec() { return timestep_vec; }

std::vector<int> &dump_data_container::get_atomscount_vec() { return atomscount_vec; }

const std::vector<std::pair<double, double>> &dump_data_container::get_max_boxbounds()
{
    // Ensure frame_box_bounds_vec has the required elements
    if (frame_box_bounds_vec.empty() || frame_box_bounds_vec[0].size() < 3)
    {
        throw std::runtime_error("frame_box_bounds_vec is either empty or incorrectly sized.");
    }

    // Initialize bounds with the first frame's bounds
    std::pair<double, double> x_bounds = frame_box_bounds_vec[0][0];
    std::pair<double, double> y_bounds = frame_box_bounds_vec[0][1];
    std::pair<double, double> z_bounds = frame_box_bounds_vec[0][2];

    // Loop through all frames to find the global min and max for each axis
    for (const auto &frame : frame_box_bounds_vec)
    {
        // X bounds update
        if (frame[0].first < x_bounds.first)
        {
            x_bounds.first = frame[0].first;
        }
        if (frame[0].second > x_bounds.second)
        {
            x_bounds.second = frame[0].second;
        }

        // Y bounds update
        if (frame[1].first < y_bounds.first)
        {
            y_bounds.first = frame[1].first;
        }
        if (frame[1].second > y_bounds.second)
        {
            y_bounds.second = frame[1].second;
        }

        // Z bounds update
        if (frame[2].first < z_bounds.first)
        {
            z_bounds.first = frame[2].first;
        }
        if (frame[2].second > z_bounds.second)
        {
            z_bounds.second = frame[2].second;
        }
    }

    // Store the final max bounds for each axis
    max_boxbounds[0] = x_bounds;
    max_boxbounds[1] = y_bounds;
    max_boxbounds[2] = z_bounds;

    return max_boxbounds;
}
// std::pair<std::vector<int>, std::vector<int>> get_displacements(double disp_threshold)
// {
// }
