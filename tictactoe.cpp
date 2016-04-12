#include<bits/stdc++.h>

using namespace std;

int toBase10(vector<int> in){
  int n = in.size();
  int base = 1;
  int out = 0;
  for(int i = n-1; i >=0 ; --i){
    out += base*in[i];
    base*=3;
  }
  return out;
}

int winner(vector<int> in){
  for(int i = 0; i < 3; ++i){
    if(in[i*3+0] == in[i*3+1] && in[i*3+0] == in[i*3+2] && in[i*3+0] !=0){
      return in[i*3];
    }
  }
  for(int i = 0; i < 3; ++i){
    if(in[0*3+i] == in[1*3+i] && in[0*3+i] == in[2*3+i] && in[0*3+i] !=0){
      return in[0*3+i];
    }
  }
  if(in[0]==in[4] && in[0]==in[8] && in[0]!=0){
    return in[0];
  }
  if(in[2]==in[4] && in[2]==in[6] && in[2]!=0){
    return in[2];
  }
  return 0;
}

bool full(vector<int> in){
  bool out = true;
  for(int i = 0; i < 9; ++i){
    if(!in[i]) {
      out = false;
      break;
    }
  }
  return out;
}

vector<int> putmove(vector<int> in, int move, int player){
  in[move] = player;
  return in;
}

bool movePossible(vector<int> in, int move){
  return(!in[move]);
}

int getFutureWinner(vector<int> in, int player);

pair<int, int> getBestMove(vector<int> in, int player){
  vector<int> results(9, 0);
  for(int i = 0; i < 9; ++i){
    if(!movePossible(in, i)){
      results[i] =-1;
      continue;
    }
    vector<int> m = putmove(in, i, player);
    results[i] = getFutureWinner(m, 3-player);
  }

  for(int i = 0; i < 9; ++i){
    if(results[i]==player){
      return {i, results[i]};
    }
  }

  for(int i = 0; i < 9; ++i){
    if(results[i]==0){
      return {i, results[i]};
    }
  }

  return {0, 3-player};
}

vector<int> winnerList(19684, -1);	      

int getFutureWinner(vector<int> in, int player){
  int decimal = toBase10(in);
  if(winnerList[decimal]!=-1) return winnerList[decimal];
  int immediateWinner = winner(in);
  if(immediateWinner){
    return immediateWinner;
  }
  if(full(in)){
    return 0;
  }

  winnerList[decimal] = getBestMove(in, player).second;
  return winnerList[decimal];
 
}


void printState(vector<int> in){
  cout<<"\n";
  for(int y = 0; y < 3; ++y){
    if(y>0) {
      for(int i = 0; i < 3*3;++i)cout<<"-";
      cout<<"\n";
    }
    for(int x = 0; x < 3; ++x){
      int val = in[y*3+x];
      switch(val){
      case 0:
	cout<<" ";
	break;
      case 1:
	cout<<"x";
	break;
      case 2:
	cout<<"o";
	break;
      }
      cout<<" ";
      if(x<2) cout<<"| ";
    }
    cout<<"\n";
  }
  cout<<"\n";
}

int main(){
  vector<int> state (9, 0);

  int playernr = 1;
  int ainr = 2;

  bool aiVSai = false;
  
  while (true){
    printState(state);
    cout<<"Next move: (1-9) ";
    int playermove;

    if(!aiVSai){
      cin >> playermove;
      --playermove;
      if(state[playermove]!=0){
	cout<<"\nNot a valid move!\n\n";
	continue;
      }
      state[playermove] = playernr;
    }else{
      state[getBestMove(state, playernr).first] = playernr;
    }
    int winnerNr = winner(state);
    if(winnerNr == playernr){
      
      cout<<"\n\nPlayer wins.\n\n";
      
      return 0;
    }

    if(full(state)){
      cout<<"\n\nDraw.\n\n";
      return 0;
    }
    
    state[getBestMove(state, ainr).first] = ainr;

    winnerNr = winner(state);
    if(winnerNr == ainr){
      printState(state);
      cout<<"\n\nProgram wins\n\n";
      
      return 0;
    }
  }
}
