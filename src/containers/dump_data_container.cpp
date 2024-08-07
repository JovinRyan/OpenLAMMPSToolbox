#include "containers/dump_data_container.h"

dump_data_container::dump_data_container(std::vector<double> t_vec, std::vector<int> ac_vec,
                                         std::vector<std::vector<atom>> fa_vec, std::vector<std::vector<std::pair<double, double>>> f_bb_vec)
    : timestep_vec(t_vec), atomscount_vec(ac_vec), frame_atoms_vec(fa_vec), frame_box_bounds_vec(f_bb_vec)
{
}

std::vector<double> dump_data_container::get_timestep_vec() { return timestep_vec; }

std::vector<int> dump_data_container::get_atomscount_vec() { return atomscount_vec; }

std::vector<std::pair<double, double>> dump_data_container::get_max_boxbounds()
{
    std::pair<double, double> x_bounds = frame_box_bounds_vec[0][0];
    std::pair<double, double> y_bounds = frame_box_bounds_vec[0][1];
    std::pair<double, double> z_bounds = frame_box_bounds_vec[0][2];

    for (int i; i < size(frame_box_bounds_vec); i++)
    {
        // X bounds update
        if (frame_box_bounds_vec[i][0].first < x_bounds.first)
        {
            x_bounds.first = frame_box_bounds_vec[i][0].first;
        }

        if (frame_box_bounds_vec[i][0].second > x_bounds.second)
        {
            x_bounds.second = frame_box_bounds_vec[i][0].second;
        }
        // Y bounds update
        if (frame_box_bounds_vec[i][1].first < x_bounds.first)
        {
            y_bounds.first = frame_box_bounds_vec[i][1].first;
        }

        if (frame_box_bounds_vec[i][1].second > x_bounds.second)
        {
            y_bounds.second = frame_box_bounds_vec[i][1].second;
        }
        // Z bounds update
        if (frame_box_bounds_vec[i][2].first < x_bounds.first)
        {
            z_bounds.first = frame_box_bounds_vec[i][2].first;
        }

        if (frame_box_bounds_vec[i][2].second > x_bounds.second)
        {
            z_bounds.second = frame_box_bounds_vec[i][2].second;
        }
    }

    return std::vector<std::pair<double, double>>{x_bounds, y_bounds, z_bounds};
}
