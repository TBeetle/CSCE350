#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "program5.h"
#include "gtest/gtest.h"

using namespace std;
using std::string;
using std::vector;


CRS rec_cr_soln(vector<int> cs){
  if(cs.size() == 0){
    CRS soln;
    soln.val = 0;
    //cout<<"base case 0 rec_cr"<<endl;
    return soln;
  }
  if(cs.size() == 1){
    CRS soln;
    soln.val = cs[0];
    soln.coin_indices.push_back(0);
    //cout<<"base case 1 rec_cr"<<endl;
    return soln;
  }
  //cout<<"after base cases rec_cr"<<endl;
  //cout<<"cs.size() = " <<cs.size()<<endl;
  int ind = cs.size()-1;
  int val = cs[cs.size()-1];
  cs.pop_back();
  CRS skip = rec_cr_soln(cs);
  cs.pop_back();
  CRS take_rest = rec_cr_soln(cs);
  int take_val = val + take_rest.val;
  if(take_val>skip.val){
    //cout<<"take case rec_cr"<<endl;
    take_rest.val = take_val;
    take_rest.coin_indices.push_back(ind);
    return take_rest;
  }
  else{
    //cout<<"skip case rec_cr"<<endl;
    return skip;
  }
  cout<<"leaving rec_cr"<<endl;
}

pair<vector<int>,CRS> gen_cr_prob(int sz){
  vector<int> coins;
  for(int i = 0; i<sz; ++i){
    coins.push_back(rand()%10 + 1 );
  }
  return pair<vector<int>,CRS>(coins,rec_cr_soln(coins));
}

bool valid_indices (vector<int> coins, CRS student){
  for(int ind : student.coin_indices){
    if(ind < 0 || ind >= coins.size()) return false;
  }
  return true;
}

bool no_duplicate_or_adjacent_indices(CRS student){
  vector<int> inds = student.coin_indices;
  std::sort(inds.begin(),inds.end() );
  for(int i = 1;i<inds.size();++i){
    if(inds[i] - inds[i-1] < 2) return false;

  }
  return true;
}

void print_cr_soln(string msg, CRS crs, CRS targ_crs){
  cout << msg << endl;
  cout <<" your val" << crs.val <<", target = " << targ_crs.val <<endl;
}

TEST(rec_cr_soln,no_credit){
  //from slides
  vector<int> coins {5,1,2,10,6,2};
  CRS soln = rec_cr_soln(coins);
  ASSERT_EQ(soln.val, 17) << "rec_cr failed, wrong val";
  ASSERT_TRUE(valid_indices(coins,soln))<< "rec_cr failed, invalid_indices (out of bounds";
  ASSERT_TRUE(no_duplicate_or_adjacent_indices(soln))<<"you have a duplicate or adjacent indices";
}

int cr_num_random_trials = 50;
int cr_rand_prob_size = 20;

TEST(rec_cr_soln_random,no_credit){
  for(int i = 0; i< cr_num_random_trials; ++i){
    pair<vector<int>,CRS> prob  = gen_cr_prob(cr_rand_prob_size);
    vector<int>& coins = prob.first;
    CRS& soln = prob.second;
    CRS call = rec_cr_soln(coins);
    ASSERT_EQ(soln.val, call.val) << "rec_cr failed, wrong val";
    ASSERT_TRUE(valid_indices(coins,call))<< "rec_cr failed, invalid_indices (out of bounds";
    ASSERT_TRUE(no_duplicate_or_adjacent_indices(call))<<"you have a duplicate or adjacent indices";
    int val = 0;
    for(int ci : call.coin_indices)
    val += coins[ci];
    ASSERT_EQ(val, call.val) << "the coins the you have don't add up to your value";
  }
}

TEST(cr_soln_random_val,random){
  for(int i = 0; i< cr_num_random_trials; ++i){
    pair<vector<int>,CRS> prob  = gen_cr_prob(cr_rand_prob_size);
    vector<int>& coins = prob.first;
    CRS& soln = prob.second;
    CRS call = solve_coin_row(coins);
    ASSERT_EQ(soln.val, call.val) << "rec_cr failed, wrong val";
    //ASSERT_TRUE(valid_indices(coins,call))<< "rec_cr failed, invalid_indices (out of bounds";
    //ASSERT_TRUE(no_duplicate_or_adjacent_indices(call))<<"you have a duplicate or adjacent indices";
  }
}

TEST(cr_soln_random_soln,random){
    for(int i = 0; i< cr_num_random_trials; ++i){
        pair<vector<int>,CRS> prob  = gen_cr_prob(cr_rand_prob_size);
        vector<int>& coins = prob.first;
        CRS& soln = prob.second;
        CRS call = solve_coin_row(coins);
        ASSERT_EQ(soln.val, call.val) << "rec_cr failed, wrong val";
        ASSERT_TRUE(valid_indices(coins,call))<< "rec_cr failed, invalid_indices (out of bounds)";
        ASSERT_TRUE(no_duplicate_or_adjacent_indices(call))<<"you have a duplicate or adjacent indices";
        int val = 0;
        for(int ci : call.coin_indices)
          val += coins[ci];
        ASSERT_EQ(val, call.val) << "the coins the you have don't add up to your value";
    }
}


TEST(cr_soln_slide, slide_example){
    //from slides
    vector<int> coins {5,1,2,10,6,2};
    CRS soln = solve_coin_row(coins);
    ASSERT_EQ(soln.val, 17) << "solve_coin_row failed, wrong val";
    ASSERT_TRUE(valid_indices(coins,soln))<< "solve_coin_row failed, invalid_indices (out of bounds";
    ASSERT_TRUE(no_duplicate_or_adjacent_indices(soln))<<"you have a duplicate or adjacent indices";
}

const int rc_num_random_trials = 20;
const int rc_rand_prob_size_x = 10;
const int rc_rand_prob_size_y = 8;
const int size_var = 1;
const double coin_chance = 0.2;

int rand_size(int v){
  return v - size_var + rand() % (2*size_var +1) ;
}

RCS rcs_rc_soln(vector< vector<bool> >& coins, int x, int y){
  RCS soln;
  if (x==0 && y==0) {
    soln.n = coins[0][0] ? 1 : 0;
    return soln;
  }
  RCS u_soln;
  RCS l_soln;
  if(x>0){
    l_soln = rcs_rc_soln(coins,x-1,y);
  }
  else l_soln.n = -1;
  if(y>0){
    u_soln = rcs_rc_soln(coins,x,y-1);
  }
  else u_soln.n = -1;
  if(l_soln.n >u_soln.n){
    soln = l_soln;
    soln.moves.push_back(Right);
  }
  else{
    soln = u_soln;
    soln.moves.push_back(Down);
  }
  soln.n += coins[y][x] ? 1 :0;
  return soln;
}

RCS rec_rc_soln(vector<vector<bool> > coins){
  int w = coins[0].size();
  int h = coins.size();
  return rcs_rc_soln(coins,w-1,h-1);
}

std::pair<RCS,vector<vector <bool> > > gen_rc_problem(){
  int w = rand_size(rc_rand_prob_size_x);
  int h = rand_size(rc_rand_prob_size_y);
  vector<vector< bool > > coins;
  for(int r = 0; r<h;++r){
    coins.push_back(vector<bool>());
    for(int c=0;c<w;++c){
      coins[r].push_back(double(rand() )/RAND_MAX <=coin_chance);
    }
  }
  RCS soln = rec_rc_soln(coins);
  return std::pair<RCS,vector<vector<bool> > >(soln,coins);
}

string pretty_soln_target_comp(vector<vector<bool> >coins, RCS soln, RCS target){
  string s = "\n";
  s+="\nExpected n = " + to_string(target.n)+" , got n ="+ to_string(soln.n);
  s+="\nFor coins:";
  s+="\n";
  for(bool b:coins[0]) s+="=";
  for(int r = 0;r<coins.size();++r){
    s+="\n";
    for(int c =0;c<coins[0].size();++c){
      if (coins[r][c]) s+="o";
      else s+="-";
    }
  }
  s+="\n";
  for(bool b:coins[0]) s+="=";
  s+="\n\n";
  s+="_A_  valid path = ";
  for(Move m: target.moves) {
    s+= m==Right?"R,":"D,";
  }
  s+="\n";
  s+="your chosen path = ";
  for(Move m: soln.moves) {
    s+= m==Right?"R,":"D,";
  }
  s+="\n";
  return s;
}

void valid_rcs (vector<vector<bool> > coins, RCS rcs,string msg){
  int w = coins[0].size();
  int h = coins.size();
  int expectedRights = w-1;
  int expectedDowns  = h-1;
  int expectedNumMoves = expectedRights + expectedDowns;
  ASSERT_EQ(expectedNumMoves,rcs.moves.size())<<"your number of moves is wrong"<<msg;
  int actualRights=0,actualDowns=0;
  for(Move m: rcs.moves){
    if(m==Down) ++actualDowns;
    else        ++actualRights;
  }
  ASSERT_EQ(expectedDowns,actualDowns)<<"You had more/less Downs than expected"<<msg;
  ASSERT_EQ(expectedRights,actualRights)<<"You had more/less Rights than expected"<<msg;
  int x = 0;
  int y = 0;
  int n = 0;
  while( x<=w-1 && y<= h-1 ){
    if(coins[y][x]) ++n;
    if (rcs.moves[x+y] == Right) ++x;
    else ++y;
  }
  ASSERT_EQ(n,rcs.n)<<"Your path does not match the target amount of coins (in rcs)"<<msg;
}

TEST(rec_rc_soln_random,no_credit){
  srand (time(NULL));
  for(int i = 0; i< rc_num_random_trials; ++i){
    pair<RCS,vector<vector<bool> > > prob  = gen_rc_problem();
    vector<vector<bool> >& coins = prob.second;
    RCS& soln = prob.first;
    RCS call = rec_rc_soln(coins);
    ASSERT_EQ(soln.n, call.n) << "rec_cr failed, wrong val";
  }
}

TEST(dp_rc_soln_random_val,random){
  srand (time(NULL));
  for(int i = 0; i< rc_num_random_trials; ++i){
    pair<RCS,vector<vector<bool> > > prob  = gen_rc_problem();
    vector<vector<bool> >& coins = prob.second;
    RCS& soln = prob.first;
    RCS call = solve_robot_coin(coins);
    ASSERT_EQ(soln.n, call.n) << "rec_cr failed, wrong val"<<pretty_soln_target_comp(coins,call,soln);
  }
}



TEST(dp_rc_soln_random_soln,random){
  srand (time(NULL));
  for(int i = 0; i< rc_num_random_trials; ++i){
    pair<RCS,vector<vector<bool> > > prob  = gen_rc_problem();
    vector<vector<bool> >& coins = prob.second;
    RCS& soln = prob.first;
    RCS call = solve_robot_coin(coins);
    ASSERT_EQ(soln.n, call.n) << "rec_cr failed, wrong val";
    string msg = pretty_soln_target_comp(coins,call,soln);
    valid_rcs(coins,call,msg);
  }
}
