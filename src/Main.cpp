#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>

//#define NUMOFKEY 3;
#define NOT_DEFINED  -1;

using namespace std;
int goto_map[127][127];
int Fail_map[100];

int newstate = 0;

char* enter(char * words);

void fail(multimap<int, char*>& multi_map);

void delta_map(int(*del)[127]);


char *output[100];
char(*buff[])[50];


char buffofwords[50];




class KEY{
	//char words[50];
public:
	char words[50];

	void insert_key(char *_words){
		//strcpy_s(words, _words);
		strcpy_s(words, _words);
	}
	char* Get_Key(){
		//cout << " keywords : " << words << endl;
		return words;
	}
	friend ostream& operator<<(ostream& os, const KEY& k);

};




void GOTO(int(*mapp)[127], vector<char *> v, int length){
	//void GOTO(int(*mapp)[127], vector<KEY> v, int length  ){

	cout << "GOTO \C7Լ\F6 ȣ\C3\E2" << endl;
	cout << " num of ketwords : " << length << endl;


	for (int i = 0; i < 127; i++){
		for (int j = 0; j < 127; j++){
			goto_map[i][j] = 0;



		}
	}
	for (int t = 0; t < 100; t++){
		output[t] = "";
		//if (t == 0) { output[t] = v[0]; }
		//else{ output[t] = "\0"; }


	}
	//char(*buf)[50] = { 0, };

	for (int j = 0; j < 4; j++){
		//buf = enter(v[j].words);
		//cout << "1. input keyword : " << *buf << endl;
		cout << "1. input keyword : " << enter(v[j]) << endl;

	}

	cout << "==========================" << endl;


	for (int stat = 0; stat < 100; stat++){

		cout << "2. output keyword[" << stat << "] = " << output[stat] << endl;

	}


}


char* enter(char * words){
	//char (*  enter(char * words))[50]{

	int init_state = 0;
	cout << endl;
	cout << "===========================" << endl;
	cout << "enter function ȣ\C3\E2" << endl;
	cout << " keyword input : " << words << endl;
	int state = 0; int j = 0;
	int size = strlen(words); int index = 0;
	char temp[50];

	strcpy_s(temp, words);




	int inc = 0;
	while ((goto_map[state][(int)temp[j]] != 0) && (j<size)){
		//while ( ( goto_map[state][(int)temp[j]]  != 0 ) && (*words++ != '\0') ){
		cout << "temp[" << j << "] =" << (char)temp[j] << endl;

		state = goto_map[state][(int)temp[j]];

		j = j + 1;



	}

	for (int p = j; p < size; p++){
		newstate = newstate + 1;
		goto_map[state][(int)temp[p]] = newstate;
		state = newstate;
	}
	cout << "new state : " << newstate << endl;
	cout << "==================================" << endl;

	output[state] = words;

	printf("address output[%d] = %x\n", state, output[state]);
	//cout << "address output[" << state << "] = " << &(output[state]) << endl;
	//cout << "address " <<words << " = " << &words << endl;
	printf("addres of %s = %x\n", words, words);
	return words;
}
//
ostream& operator<<(ostream& os, KEY& k){
	os << k.words << endl;
	return os;
}

//fail function -----------------------------------------------------------------------------------------------

void fail(multimap<int, char*>& multi_map)
{
	Fail_map[100] = { 0, }; int state = 0;
	cout << "fail function call =====" << endl;
	output[0] = "";
	/*output[0] \C0\BA fail \C7Լ\F6 ȣ\C3\E2\BD\C3 \C7ѹ\F8\B4\F5 \C3ʱ\E2ȭ \C7\D8\C1־\EE\BE\DF \C7Ѵ\D9.
	\B1׷\B8\C1\F6 \BE\CA\C0\B8\B8\E9 fail \C7Լ\F6ȣ\C3\E2\B0\FA \B5\BF\BDÿ\A1 mulitmap\BF\A1\BC\AD (0,NULL)\B7\CE \B5\E9\BE\BC\AD \B0\AA\C0\CC \B5\E9\BE\C1\F6 \BEʴ´\D9 \C1\EF \B0\F8\B9鹮\C0ڿ\AD
	""\C0\BB \B4\EB\C0Խÿ\A1 \B9\AE\C0ڿ\ADũ\B1Ⱑ \BE\F8\B1\E2 \B6\A7\B9\AE\BF\A1 NULL\B7\CE \B5\E9\BE\B0\D4 \B5ȴ\D9  */
	cout << " outpit[0] = " << output[0] << endl;
	queue<int > queue;
	int in = 0; int s = 0;
	for (int a = 0; (a < 127); a++){
		s = goto_map[0][a];
		if (s>0){
			in++;
			cout << "queue in state : " << s << endl;
			queue.push(s);
			Fail_map[s] = 0;
			cout << "goto_map[0][" << a << "] = " << goto_map[0][a] << endl;
		}
	}




	while (!queue.empty()){
		cout << "queue not empty()" << endl;
		int r = queue.front();
		cout << " queue front() : " << r << endl;
		queue.pop();
		cout << endl;
		for (int a = 0; a < 127; a++){
			s = goto_map[r][a];
			if (s > 0){
				cout << "s  = " << s << endl; cout << endl;
				queue.push(s);
				state = Fail_map[r];
				while (goto_map[state][a] == 0){
					state = Fail_map[state];
					if (state == 0) break;
				}//end of while
				Fail_map[s] = goto_map[state][a];
				if (output[s] != ""){
					multi_map.insert(make_pair(s, output[s]));
					multi_map.insert(make_pair(s, output[Fail_map[s]]));
				}

			}//endOfIf

		}//end of for
	}//end of while

}


//delta function -----------------------------------------------------------------------------------------------

void delta_map(int del[127][127])
{


	cout << "delta function call =====" << endl;
	queue<int > queue2;
	int s = 0;
	for (int a = 0; (a < 127); a++){
		del[0][a] = goto_map[0][a];
		s = goto_map[0][a];
		if (s>0){

			cout << "queue in state : " << del[0][a] << endl;
			queue2.push(s);
			//	cout << "goto_map[0][" << a << "] = " << goto_map[0][a] << endl;
		}//end of if
	}//end of for




	while (!queue2.empty()){
		cout << "queue not empty()" << endl;
		int r = queue2.front();
		cout << " queue front() : " << r << endl;
		queue2.pop();

		for (int a = 0; a < 127; a++){
			s = goto_map[r][a];
			if (s > 0){

				queue2.push(s);
				del[r][a] = s;

			}
			else{
				del[r][a] = del[Fail_map[r]][a];
			}

		}//end of for
	}//end of while


}//end of delta function


int main(int argc, char** argv)
{

	int length = 0;
	KEY key[4];
	vector<KEY> v;

	const int NUMofKey = 4;
	vector<char*> v2;
	char *p[NUMofKey] = { "he", "she", "his", "hers" }; //Reserved keywords

	for (int i = 0; i < 4; i++){
		key[i].insert_key(p[i]);

		//	key[i].Get_Key();
		v.push_back(key[i]);
		v2.push_back(p[i]);
		//cout << "keyworks ["<<i<<"] = "<<v.at(i).Get_Key() << endl;
		cout << "keyword [" << i << "] = " << v2[i] << endl;
	}

	vector<KEY>::iterator num = v.begin();
	int k = 0;
	cout << "==========iterator use============= " << endl;
	for (vector<KEY>::iterator it = num; it != v.end(); it++){

		cout << it->Get_Key() << endl;
		length++;

	}
	cout << "GOTO FUNCTION" << endl;


	//GOTO(goto_map ,v, length);

	GOTO(goto_map, v2, length);






	multimap<int, char*> output_m;


	cout << "before failfunc call   " << endl;

	for (int i = 0; i < 100; i++){

		output_m.insert(make_pair(i, output[i])); //Initialization of multimap (multimap\C0\BA \B9\AB\C1\B6\B0\C7 \C3ʱ\E2ȭ\C7ؾ\DF\C7Ѵ\D9 \B1׷\B8\C1\F6 \BE\CA\C0\B8\B8\E9 fail\C7Լ\F6 ȣ\C3\E2\BD\C3 \B3ΰ\AA\C0\CC \B5\E9\BE \BF\C0\B7\F9)

		cout << output_m.find(i)->first << "," << output_m.find(i)->second << endl;


	}

	for (multimap<int, char*>::iterator iter = output_m.begin(); iter != output_m.end(); ++iter){
		cout << iter->first << ", " << iter->second << endl;
	}

	/*fail function call*/
	fail(output_m);




	cout << "after failfunc call   " << endl;

	for (int i = 0; i < 100; i++){

		cout << output_m.find(i)->first << "," << output_m.find(i)->second << endl;;
	}

	for (multimap<int, char*>::iterator iter = output_m.begin(); iter != output_m.end(); ++iter){
			cout << iter->first << ", " << iter->second << endl;

	}




	int del[127][127] = {0, }; //Initialization of delta map
	delta_map(del);



	string str3;
	string buff;

	cout << "input string :";
	getline(cin, str3);

	int n = str3.size();
	cout << "size of string : " << n << endl;
	string *s_temp = new string[n];

	int leng = 0; int col = 0;
	while (leng < n){

		if (str3.at(leng)!=' '){

			buff += str3[leng];
		}
		else{

			buff = "";
			col++;

		}
		s_temp[col] = buff;
		cout << "str2[" << col << "] = " << s_temp[col] << endl;
		//cout << str3[leng] << endl;
		leng++;
	}

	int numOfwords = 0;
	while (numOfwords < (col + 1 )){
		int size = s_temp[numOfwords].size();
		cout << numOfwords+1 <<"-th word of sentence : "<< s_temp[numOfwords]<<" , size : "<<size<<endl;


		int n = 0; int numOfchar = 0;  char ch = ' '; char first_ch = ' '; int s = 0; int state = 0;
		while (n < size){
			first_ch = s_temp[numOfwords][0];


			s = goto_map[0][(int)first_ch];
			if (s == 0){
				cout << "Sorry, but we coudln`t find keywords for " <<s_temp[numOfwords]<< endl;
				break;
			}
			for (int a = 0; a < 127; a++){

				while(s>0 && (n < s_temp[numOfwords].size())){
					if (n == 0)cout << " 0 -> ";
					ch = s_temp[numOfwords][n++];

					state = del[state][(int)ch];
					if (state == 0) { //if next state is not defined
						break;
					}
					else{
						cout << ch << "(" << state << ")";
					}
					cout << " -> ";
				}//end of while

			}//end of for statement

		}//end of while statement
		cout << endl;
		numOfwords++;
	}//end of while statement

	delete[] s_temp;
	return 0;

}





