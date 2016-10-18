#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include <map>
#include <vector>
#include <utility>

using namespace std;

typedef pair<string,double> P;

struct node
{
	std::vector<struct node *> parents;
	std::map<string, double> probabilityTable;	
};

int main(int argc, char *argv[])
{
	string buffer,eater,builder,aux;	
	char devourer,catcher;

	double readerP;

	vector<string>queries;
	vector<string> nodes;
	vector<P>prob;

	int ite;
	int sect = 0;
	cout << "STARTING...\n";
	while(sect < 3){
		getline(cin,buffer);
		//cout << "Reading std\n";
		if(buffer.compare("[Nodes]")==0){
			ite=0;//iterator
			cout << "Nodes:\n";
			getline(cin,buffer);
			for(int i=0;i < buffer.length();i++){
				if(buffer[i]==','){
					nodes.push_back(builder);
					ite++;
					cout << '\n';
				}else if(buffer[i]==' '){
					builder="";
				}else{
					builder+=buffer[i];
					cout << buffer[i];
				}
			}
			cout << '\n';
			sect++;
		}else if(buffer.compare("[Probabilities]")==0){
			cout << "Probabilities:\n";
			while(buffer.compare("")!=0){
				getline(cin,buffer);
				//link nodes with their parents
				for(int i=0;i < buffer.length();i++){
					if(buffer[i]=='|'){
						cout << " is child of: ";
					}else if(buffer[i]=='+'||buffer[i]=='-'||buffer[i]==' '||buffer[i]=='='||buffer[i]=='.'||(buffer[i]>=48&&buffer[i]<=57));
					else{
						cout << buffer[i];
					}
				}
				cout << '\n';
				//probability table
				builder="";
				for(int i=0;i < buffer.length();i++){
					if(buffer[i]=='='){
						break;
					}else{
						builder+=buffer[i];
					}
				}
				stringstream extract(buffer);
				
				do{
					extract >> devourer;
				}while(devourer!='=');

				
				extract >> readerP;

				prob.push_back(make_pair(builder,readerP));

				cout << "P("<< builder << ")= " << readerP << "\n";
			}
			sect++;
		}else if (buffer.compare("[Queries]")==0){
			cout << "Queries:\n";
			sect++;
		}
		
	}
/*
	cout << "Nodes\n";
	for(int i=0;i<nodes.size();i++){
		cout << nodes[i] << '\n';
	}
*/
	return 0;
}