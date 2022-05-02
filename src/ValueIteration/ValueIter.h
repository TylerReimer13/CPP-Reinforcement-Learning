#pragma once
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


class ValueIteration {
	private:
		vector<int> grid_dims;
		vector<vector<double>> grid;
		vector<int> start;
		vector<int> goal;
		double discount_factor;
		vector<string> actions;
		unordered_map<string, vector<int>> action_map;

		vector<int> get_next_state(vector<int>& curr_state, string& action); 
		double get_reward(vector<int>& state);
		bool check_legal_move(vector<int>& state);

	public:
		ValueIteration(vector<int>& grid_dims, vector<int>& start, vector<int>& goal, double discount_factor);
		void show_grid();
		void update_utility();
};
