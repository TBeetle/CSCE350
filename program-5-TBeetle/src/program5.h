#ifndef PROGRAM5_H
#define PROGRAM5_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using std::vector;



typedef struct coin_row_solution{
    int val;
    std::vector< int > coin_indices;

} CRS;

/*
 * Input: vector of coins in order
 * Output: a coin_row_solution, the val set to the value of the optimal solution
 *         the coin_indices (0-indexed) set to the indices of the coins forming the optimal solution
 * Must be done with Dynamic Programming -- no points for recursive solution
 */
CRS solve_coin_row(std::vector< int> coin_row){
  CRS soln;
  int size = coin_row.size();
  vector<int> dp(size + 1, 0);
  vector<int> prev(size + 1, -1);
  prev[0] = -1;
  prev[1] = 0;
  dp[0] = 0;
  dp[1] = coin_row[0];

  for (int i = 2; i <= size; i++) {
	  int x = coin_row[i - 1] + dp[i - 2];
	  int y = dp[i - 1];
	  dp[i] = std::max(x,y);
	  if (x > y) {
		   dp[i] = x;
		  prev[i] = i - 2;
	  } else {
		   dp[i] = y;
		  prev[i] = i - 1;
	}
  }
  soln.val = dp[size];
  int index = size;
  while (index >= 2) {
	  if(prev[index] != index - 1) {
		  soln.coin_indices.push_back(index - 1);
	  }
	  index = prev[index];
  }
  if (index == 1) {
	  soln.coin_indices.push_back(0);
  }
  reverse(soln.coin_indices.begin(), soln.coin_indices.end());

  return soln;

}


/*
 * Robot coin pickup dynamic programming soln
 *
 */

enum Move {Right,Down};

typedef struct robot_coin_solution{
    int n;
    std::vector<Move> moves;
} RCS;

/*
 * Input: vector<vector<bool > > coins : (inner vector is x/column direction, index like a matrix)
 * Output: an RCS (above): n is the max number of coins, moves is a vector of moves
 *    the vector of moves must take the robot from the upper left to the lower right
 *    of course, the moves must also allow the robot to pick up the maximum number of coins
 *    think of the vector of moves that if followed from index 0, 1, ... give a the plan
 *    for the robot starting at the upper left (0,0)
 */
RCS solve_robot_coin(vector<vector<bool> > coins){
  RCS soln;
  int x = coins.size();
  int y = coins[0].size();
  vector<vector<int>> dp(x,vector<int>(y,0));

  for (int i = 0; i < x; i++) {
	for (int j = 0; j < y; j++) {
	  int fromTop = (i > 0) ? dp[i - 1][j] : 0;
	  int fromLeft = (j > 0) ? dp[i][j - 1] : 0;
	  dp[i][j] = std::max(fromTop, fromLeft) + coins[i][j];
	  }
  }

  int i = x - 1;
  int j = y - 1;
  soln.n = dp[i][j];

  while(i > 0 || j > 0) {
	  if (i > 0 && dp[i - 1][j] >= dp[i][j - 1]) {
		  soln.moves.push_back(Down);
		  i--;
	  } else {
		  soln.moves.push_back(Right);
		  j--;
	  }
  }
  reverse(soln.moves.begin(), soln.moves.end());
  return soln;
}

#endif //PROGRAM5_H
