#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

#include <algorithm>
#include <map>
#include <vector>
#include <utility>

using namespace std;

typedef pair<string,double> P;

struct node
{
	std::vector<struct node *> parents; //for 0 or N-parents; if the vector is empty, the event is Independient
	std::map<string, double> probabilityTable;  //key is X in P(X)
};

void createNodes(map<string, struct node*> &nodes,string buffer){
	string builder;
	getline(cin,buffer);
	for(int i=0;i < buffer.length();i++){
		if(buffer[i]==','){
			nodes[builder] = new node;
			cout << builder << "\n";
		}else if(i==(buffer.length()-1)){
			builder+=buffer[i];
			cout << builder << "\n";
			nodes[builder] = new node;
		}else if(buffer[i]==' '){
			builder="";
		}else{
			builder+=buffer[i];
		}
	}
}

void createBayesNetwork(map<string, struct node*> &nodes,string buffer){
	string builder, aux;
	char devourer;
	double readerProb;

	while(buffer.compare("")!=0){
		getline(cin,buffer);
		builder="";
		//link nodes with their parents
		//cout << "----\n";
		bool indexNode=false;
		for(int i=0;i < buffer.length();i++){
			if(buffer[i]=='|'){
				indexNode = true; //the node have a parent
				aux = builder;
				builder="";
				cout << "\nNode is: " << aux <<'\n';
				cout << "Its parents are: ";
			}
			if(buffer[i]=='+'||buffer[i]=='-'||buffer[i]==' '||buffer[i]=='='||buffer[i]==','||buffer[i]=='|'||(buffer[i]>=48&&buffer[i]<=57));
			else{
				builder+=buffer[i]; //construct the string key for the map of nodes
				//cout << '.';
			}
			if(indexNode){ //to make the conection in base of the dependece
				if(find((nodes[aux])->parents.begin(),(nodes[aux])->parents.end(),nodes[builder])!=(nodes[aux])->parents.end()){
					cout << " [A.K.] ";
					builder = "";
				}
				else{
					if(buffer[i]==','){
						(nodes[aux])->parents.push_back(nodes[builder]); //to create N parents
						cout << builder <<' ';
						builder="";
					}else if (buffer[i]=='=')
					{
						(nodes[aux])->parents.push_back(nodes[builder]); //if there is only one parent
						cout << builder <<' ';
						builder="";
					}
				}
			}

			if(buffer[i]=='='){
				if(!indexNode){
					aux=builder; //the node is root P(X) is independient
					cout << "\nNode: " << aux <<" is a root\n";
				}
				break; //finish the creation of the edges
			}
		}
		cout << '\n';
		//probability table
		builder="";
		for(int i=0;i < buffer.length();i++){
			if(buffer[i]=='='){
				break;
			}else if(buffer[i]==' '&&buffer[i+1]=='='); //to ignore the last blank space " ="
			else{
				builder+=buffer[i];
			}
		}

		if(builder.compare("")!=0){
			stringstream extract(buffer);
			
			do{
				extract >> devourer; //eats all chars
			}while(devourer!='=');

			
			extract >> readerProb;

			(nodes[aux])->probabilityTable[builder]=readerProb; //store the true values P(+X|Y)

			cout << "P("<< builder << ")= " << (nodes[aux])->probabilityTable[builder] << "\n";
		}

	}
}

void solveQuery(map<string, struct node*> nodes, string buffer){
	double res;
	string numerator, denominator;
	numerator="";
	denominator="";
	bool dependece=false;
	for (int i = 0; i < buffer.length(); i++){
		if(buffer[i]=='|'){
			dependece=true;
			numerator+=", ";
		}
		if(!dependece){
			if(buffer[i]!='|'){
				numerator+=buffer[i];
			}
		}else{
			if(buffer[i]!='|'){
				numerator+=buffer[i];
				denominator+=buffer[i];
			}
		}
	}

	if(denominator.compare("")==0){
		cout << numerator << "\n";
		//res = solveJoint(nodes,numerator);
	}else{
		cout << numerator << " / " << denominator << "\n";
		//res = solveJoint(nodes,numerator) / solveJoint(nodes,denominator);
	}

	//return res;
}

int main(int argc, char *argv[])
{
	std::map<string, struct node*> nodes;
	
	string buffer, builder, aux;

	char devourer;

	double readerProb;

	
	int sect = 0;
	cout << "STARTING...\n";
	while(sect < 3){
		getline(cin,buffer);
		//cout << "Reading std\n";
		if(buffer.compare("[Nodes]")==0){
			cout << "Nodes:\n";
			/*
			getline(cin,buffer);
			for(int i=0;i < buffer.length();i++){
				if(buffer[i]==','){
					nodes[builder] = new node;
					cout << builder << "\n";
				}else if(i==(buffer.length()-1)){
					builder+=buffer[i];
					cout << builder << "\n";
					nodes[builder] = new node;
				}else if(buffer[i]==' '){
					builder="";
				}else{
					builder+=buffer[i];
				}
			}
			*/
			createNodes(nodes,buffer);
			cout << '\n';
			sect++;
		}else if(buffer.compare("[Probabilities]")==0){
			cout << "Probabilities:\n";
			/*
			while(buffer.compare("")!=0){
				getline(cin,buffer);
				builder="";
				//link nodes with their parents
				//cout << "----\n";
				bool indexNode=false;
				for(int i=0;i < buffer.length();i++){
					if(buffer[i]=='|'){
						indexNode = true; //the node have a parent
						aux = builder;
						builder="";
						cout << "\nNode is: " << aux <<'\n';
						cout << "Its parents are: ";
					}
					if(buffer[i]=='+'||buffer[i]=='-'||buffer[i]==' '||buffer[i]=='='||buffer[i]==','||buffer[i]=='|'||(buffer[i]>=48&&buffer[i]<=57));
					else{
						builder+=buffer[i]; //construct the string key for the map of nodes
						//cout << '.';
					}
					if(indexNode){ //to make the conection in base of the dependece
						if(find((nodes[aux])->parents.begin(),(nodes[aux])->parents.end(),nodes[builder])!=(nodes[aux])->parents.end()){
							cout << " [A.K.] ";
							builder = "";
						}
						else{
							if(buffer[i]==','){
								(nodes[aux])->parents.push_back(nodes[builder]); //to create N parents
								cout << builder <<' ';
								builder="";
							}else if (buffer[i]=='=')
							{
								(nodes[aux])->parents.push_back(nodes[builder]); //if there is only one parent
								cout << builder <<' ';
								builder="";
							}
						}
					}

					if(buffer[i]=='='){
						if(!indexNode){
							aux=builder; //the node is root P(X) is independient
							cout << "\nNode: " << aux <<" is a root\n";
						}
						break; //finish the creation of the edges
					}
				}
				cout << '\n';
				//probability table
				builder="";
				for(int i=0;i < buffer.length();i++){
					if(buffer[i]=='='){
						break;
					}else if(buffer[i]==' '&&buffer[i+1]=='='); //to ignore the last blank space " ="
					else{
						builder+=buffer[i];
					}
				}

				if(builder.compare("")!=0){
					stringstream extract(buffer);
					
					do{
						extract >> devourer; //eats all chars
					}while(devourer!='=');

					
					extract >> readerProb;

					(nodes[aux])->probabilityTable[builder]=readerProb; //store the true values P(+X|Y)

					cout << "P("<< builder << ")= " << (nodes[aux])->probabilityTable[builder] << "\n";
				}

			}*/
			createBayesNetwork(nodes,buffer);
			sect++;
		}else if (buffer.compare("[Queries]")==0){
			cout << "Queries:\n";
			getline(cin,buffer);
			while(buffer.compare("")!=0){
				solveQuery(nodes,buffer);
				getline(cin,buffer);
			}
			sect++;
		}
	}

	return 0;
}