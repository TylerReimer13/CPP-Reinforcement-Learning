#include <iostream>
#include <vector>
#include <unordered_map>
#include "PolicyEval.h"


using namespace std;


PolicyEvaluation::PolicyEvaluation(vector<int>& grid_dims, vector<int>& start, vector<int>& goal, unordered_map<string, double>& policy, double discount_factor) {
	this->grid_dims = grid_dims;
	vector<vector<double>> zeros_grid(grid_dims[0], vector<double> (grid_dims[1], 0.));
	this->grid = zeros_grid;

	this->policy = policy;

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


void PolicyEvaluation::show_grid() {
	for (int i = 0; i < grid_dims[0]; i++) {
		for (int j = 0; j < grid_dims[1]; j++) {
			printf("%11f", grid[i][j]);
		}
		cout << endl;
	}
};


double PolicyEvaluation::get_reward(vector<int>& state) {
	return -1.;
}


vector<int> PolicyEvaluation::get_next_state(vector<int>& curr_state, string& action) {
	vector<int> next_state = {curr_state[0] + action_map[action][0], curr_state[1] + action_map[action][1]};
	return next_state;
}


bool PolicyEvaluation::check_legal_move(vector<int>& state) {
	if (state[0] < 0 || state[1] < 0 || state[0] >= grid_dims[0] || state[1] >= grid_dims[1])
		return false;

	return true;
}


void PolicyEvaluation::update_value() {
	vector<vector<double>> temp_grid = grid;
	vector<int> state = {};
	vector<int> next_state = {};
	double reward = 0.;


	for (int r = 0; r < grid_dims[0]; r++) {
		for (int c = 0; c < grid_dims[1]; c++) {
			double vk_1 = 0.;
			state = {r, c};
			
			for (string& action : actions) {
				next_state = get_next_state(state, action);
				if (!check_legal_move(next_state)) {
					next_state = state;
				}
				reward = get_reward(next_state);
				vk_1 += policy[action] * (reward + (discount_factor * grid[next_state[0]][next_state[1]]));
			}
			temp_grid[state[0]][state[1]] = vk_1;
		}
	}
	temp_grid[start[0]][start[1]] = 0.;
	temp_grid[goal[0]][goal[1]] = 0.;

	grid = temp_grid;
}


int main() {
	vector<int> start = {0, 0};
	vector<int> goal = {4, 4};
	vector<int> rows_cols = {5, 5};

	unordered_map<string, double> policy;
	policy["up"] = .25;
    policy["down"] = .25;
    policy["left"] = .25;
    policy["right"] = .25;


	PolicyEvaluation policy_eval(rows_cols, start, goal, policy, 1.);

	for (int i = 0; i < 1000; i++) {
		policy_eval.update_value();
	}

	policy_eval.show_grid();
	
	return 0;
};