#pragma once
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


class PolicyEvaluation {
	private:
		vector<int> grid_dims;
		vector<vector<double>> grid;
		vector<int> start;
		vector<int> goal;
		double discount_factor;
		vector<string> actions;
		unordered_map<string, vector<int>> action_map;
		unordered_map<string, double> policy;

		vector<int> get_next_state(vector<int>& curr_state, string& action); 
		double get_reward(vector<int>& state);
		bool check_legal_move(vector<int>& state);

	public:
		PolicyEvaluation(vector<int>& grid_dims, vector<int>& start, vector<int>& goal, unordered_map<string, double>& policy, double discount_factor);
		void show_grid();
		void update_value();
};
