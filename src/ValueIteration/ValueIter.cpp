#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "ValueIter.h"


using namespace std;


ValueIteration::ValueIteration(vector<int>& grid_dims, vector<int>& start, vector<int>& goal, double discount_factor) {
	this->grid_dims = grid_dims;
	vector<vector<double>> zeros_grid(grid_dims[0], vector<double> (grid_dims[1], 0.));
	this->grid = zeros_grid;

    this->start = start;
    this->goal = goal;
    this->discount_factor = discount_factor;

    this->actions = {"up", "down", "left", "right"};

    vector<int> up = {-1, 0};
    this->action_map["up"] = up;
    vector<int> down = {1, 0};
    this->action_map["down"] = down;
    vector<int> left = {0, -1};
    this->action_map["left"] = left;
    vector<int> right = {0, 1};
    this->action_map["right"] = right;

};


void ValueIteration::show_grid() {
	for (int i = 0; i < grid_dims[0]; i++) {
		for (int j = 0; j < grid_dims[1]; j++) {
			printf("%11f", grid[i][j]);
		}
		cout << endl;
	}
};


double ValueIteration::get_reward(vector<int>& state) {
	if (state == goal) 
		return 10.;

	return -1.;
}


vector<int> ValueIteration::get_next_state(vector<int>& curr_state, string& action) {
	vector<int> next_state = {curr_state[0] + action_map[action][0], curr_state[1] + action_map[action][1]};
	return next_state;
}


bool ValueIteration::check_legal_move(vector<int>& state) {
	if (state[0] < 0 || state[1] < 0 || state[0] >= grid_dims[0] || state[1] >= grid_dims[1])
		return false;

	return true;
}


void ValueIteration::update_utility() {
	vector<vector<double>> temp_grid = grid;
	vector<int> state = {};
	vector<int> next_state = {};
	double reward = 0.;
	double vk_max = 0.;


	for (int r = 0; r < grid_dims[0]; r++) {
		for (int c = 0; c < grid_dims[1]; c++) {
			vector<double> vk_next = {};
			state = {r, c};
			
			for (string& action : actions) {
				next_state = get_next_state(state, action);
				if (!check_legal_move(next_state)) {
					next_state = state;
				}
				reward = get_reward(next_state);
				vk_next.push_back((reward + (discount_factor * grid[next_state[0]][next_state[1]])));
			}

			vk_max = *max_element(vk_next.begin(), vk_next.end());
			temp_grid[state[0]][state[1]] = vk_max;
		}
	}

	grid = temp_grid;
}


int main() {
	vector<int> start = {0, 0};
	vector<int> goal = {4, 4};
	vector<int> rows_cols = {5, 5};

	ValueIteration value_iter(rows_cols, start, goal, .75);

	for (int i = 0; i < 1000; i++) {
		value_iter.update_utility();
	}

	value_iter.show_grid();
	
	return 0;
};