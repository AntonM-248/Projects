#include <iostream>
#include <vector>
using namespace std;

//checks if any subset of a set of numbers add up to a target value.
//it generates all subsets through a complicated nested for loop.

vector<int> remove_if_greater(int targe, vector<int> se){
	vector<int> result = {1};
	for(int i = 0; i < se.size(); i++){
		if((i == 0) && (se[i] < targe)){
			result[i] = se[i];
		}
		if((i != 0) && (se[i] < targe)){
			result.push_back(se[i]);
		}
	}
	return result;
}

void print_vector(vector<int> nums){
	for(int i = 0; i < nums.size(); i++){
		cout<<nums[i]<<" ";
	}
	cout<<endl;
}

int sum_up(vector<int> result){
	int sum = 0;
	for(int i = 0; i < result.size(); i++){
		sum = sum + result[i];
	}
	return sum;
}

bool check_for_repeats(vector<int> nums){
	for(int i = 0; i < nums.size(); i++){
		for(int j = 0; j < nums.size(); j++){
			if(j != i){
				if(nums[j] == nums[i]){
					cout<<"repeat   ";
					return true;
				}
			}
		}
	}
}

int generate_pascal(int row, int col){
	if(row < 2){
		return 1;
	}
	else{
		vector<vector<int>> triangle(row+1);
		vector<int> row0(1);
		vector<int> row1(2);
		row0[0] = 1;
		row1[0] = 1;
		row1[1] = 1;
		triangle[0] = row0;
		triangle[1] = row1;
		for(int i = 2; i <= row; i++){
			vector<int> newRow(i+1);
			for(int j = 0; j <= i; j++){
				if((j == 0) || (j == i)){
					newRow[j] = 1;
				}
				else{
					newRow[j] = triangle[i-1][j-1] + triangle[i-1][j];
				}
			}
			triangle[i] = newRow;
		}
		int result = triangle[row][col + 1];
		return result;
	}
}

vector<int> find_subsets(int targt, vector<int> result){
	return result;
}

vector<vector<int>> generate_combinations_of_size_one(vector<int> set){
	vector<vector<int>> results;
	for(int i = 0; i < set.size(); i++){
		vector<int> combination;
		combination.push_back(set[i]);
		results.push_back(combination);
	}
	return results;
}

vector<vector<vector<int>>> generate_combinations_of_any_size(vector<int> set2){
	vector<vector<vector<int>>> results;
	vector<vector<int>> set = generate_combinations_of_size_one(set2);
	results.push_back(set);
	vector<vector<vector<int>>> last_pos;
	vector<vector<int>> positions0;
	for(int i = 1; i <= set2.size(); i++){
		vector<int> position0;
		position0.push_back(i % set2.size());
		positions0.push_back(position0);
	}
	last_pos.push_back(positions0);
	for(int i = 1; i < set2.size(); i++){
		vector<vector<int>> combinations;
		vector<vector<int>> positions;
		for(int j = 0; j < results[i-1].size(); j++){
			for(int k = last_pos[i-1][j][0]; k < set2.size(); k++){
				if(last_pos[i-1][j][0] != 0){
					vector<int> combination;
					vector<int> position;
					combination = results[i-1][j];
					combination.push_back(set2[k]);
					combinations.push_back(combination);
					position.push_back((k+1) % set2.size());
					positions.push_back(position);
				}
			}
		}
		results.push_back(combinations);
		last_pos.push_back(positions);
	}
	cout<<"Done";
	return results;
}

int main(){
	int target = 999999999;
	//vector<int> set = {1, 5, 10, 50, 100, 999};
	vector<int> set = {1, 2, 3, 4, 5, 6};
	vector<int> result;
	result = remove_if_greater(target, set);
	result = find_subsets(target, result);
	for(int i = 0; i < result.size(); i++){
		if(i < (result.size() -1)){
			cout<<result[i]<<", ";
		}
		else{
			cout<<result[i]<<".\n";
		}
	}
	cout<<result.size()<<endl;
	/*for(int i = 0; i < combinations_of_two.size(); i++){
		for(int j = 0; j < combinations_of_two[i].size(); j++){
			cout<<combinations_of_two[i][j]<<" ";
		}
		cout<<endl;
	}*/
	vector<vector<vector<int>>> combinations_of_any_size;
	combinations_of_any_size = generate_combinations_of_any_size(result);
	for(int i = 0; i < (combinations_of_any_size.size()); i++){
		//cout<<generate_pascal(result.size(), i)<<endl<<endl;
		//vector<int>sums;
		for(int j = 0; j < combinations_of_any_size[i].size(); j++){
			//sums.push_back(sum_up(combinations_of_any_size[i][j]));
			//check_for_repeats(sums);
			//cout<<sum_up(combinations_of_any_size[i][j])<<"            ";
			for(int k = 0; k < combinations_of_any_size[i][j].size(); k++){
				cout<<combinations_of_any_size[i][j][k]<<"   ";
			}
			cout<<endl<<endl;
		}
		cout<<endl<<endl;
	}
}
