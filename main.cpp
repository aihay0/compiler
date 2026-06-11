#include <bits/stdc++.h>
using namespace std;
struct token{
	string type;
	string text;
};
string readCode(){
	string code="";
    string temp="";
    while(getline(cin,temp)){
    	temp+="\n";
    	for(auto &it:temp){
    		if(it=='\n'||it=='\t')
    			it=' ';
    	}
    	code+=temp+"\n";
    }
    return code;
}
bool isidchar(char c){
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='_';
}
bool isdigit(char c){
	return c>='0'&&c<='9';
}
void PrintTokens(vector<token> tokens){
	for(auto it:tokens)
		cout<<it.type<<" "<<it.text<<"\n";
	return;
}
vector<token> LexicalAnalysis(string code){
	vector<token> tokens;
	for(int i=0;i<code.size();i++){
		if(code[i]==' '||code[i]=='\n'||code[i]=='\t')
			continue;
		else if(code[i]==';')
			tokens.push_back({"Symbol",";"});
		else if(code[i]=='(')
			tokens.push_back({"Symbol","("});
		else if(code[i]==')')
			tokens.push_back({"Symbol",")"});
		else if(code[i]=='{')
			tokens.push_back({"Symbol","{"});
		else if(code[i]=='}')
			tokens.push_back({"Symbol","}"});
		else if(code[i]=='+')
			tokens.push_back({"Operator","+"});
		else if(code[i]=='-')
			tokens.push_back({"Operator","-"});
		else if(code[i]=='*')
			tokens.push_back({"Operator","*"});
		else if(code[i]=='/')
			tokens.push_back({"Operator","/"});
		else if(i+1<code.size()&&code[i]=='|'&&code[i+1]=='|')
			tokens.push_back({"Operator","||"}),i++;
		else if(i+1<code.size()&&code[i]=='&'&&code[i+1]=='&')
			tokens.push_back({"Operator","&&"}),i++;
		else if(code[i]=='>'){
			if(i+1<code.size()&&code[i+1]=='=')
				tokens.push_back({"Comparator",">="}),i++;
			else
				tokens.push_back({"Comparator",">"});
		}
		else if(code[i]=='<'){
			if(i+1<code.size()&&code[i+1]=='=')
				tokens.push_back({"Comparator","<="}),i++;
			else
				tokens.push_back({"Comparator","<"});
		}
		else if(code[i]=='='){
			if(i+1<code.size()&&code[i+1]=='=')
				tokens.push_back({"Comparator","=="}),i++;
			else
				tokens.push_back({"Symbol","="});
		}
		else if(i+1<code.size()&&code[i]=='!'&&code[i+1]=='=')
			tokens.push_back({"Comparator","!="}),i++;
		else if(i+2<code.size()&&code.substr(i,3)=="int"&&(i+3==code.size()||!isidchar(code[i+3])))
			tokens.push_back({"Datatype","int "}),i+=3;
		else if(i+4<code.size()&&code.substr(i,5)=="input"&&(i+5==code.size()||!isidchar(code[i+5])))
			tokens.push_back({"Reserved word","input"}),i+=4;
		else if(i+5<code.size()&&code.substr(i,6)=="output"&&(i+6==code.size()||!isidchar(code[i+6])))
			tokens.push_back({"Reserved word","output"}),i+=5;
		else if(i+7<code.size()&&code.substr(i,8)=="outputsp"&&(i+8==code.size()||!isidchar(code[i+8])))
			tokens.push_back({"Reserved word","outputsp"}),i+=7;
		else if(i+7<code.size()&&code.substr(i,8)=="outputln"&&(i+8==code.size()||!isidchar(code[i+8])))
			tokens.push_back({"Reserved word","outputln"}),i+=7;
		else if(i+1<code.size()&&code.substr(i,2)=="if"&&(i+2==code.size()||!isidchar(code[i+2])))
			tokens.push_back({"Reserved word","if"}),i++;
		else if(i+3<code.size()&&code.substr(i,4)=="else"&&(i+4==code.size()||!isidchar(code[i+4])))
			tokens.push_back({"Reserved word","else"}),i+=4;
		else if(i+2<code.size()&&code.substr(i,3)=="for"&&(i+3==code.size()||!isidchar(code[i+3])))
			tokens.push_back({"Reserved word","for"}),i+=2;
		else if(i+4<code.size()&&code.substr(i,5)=="while"&&(i+5==code.size()||!isidchar(code[i+5])))
			tokens.push_back({"Reserved word","while"}),i+=4;
		else if(i+4<code.size()&&code.substr(i,5)=="break"&&(i+5==code.size()||!isidchar(code[i+5])))
			tokens.push_back({"Reserved word","break"}),i+=4;
		else if(i+7<code.size()&&code.substr(i,8)=="continue"&&(i+8==code.size()||!isidchar(code[i+8])))
			tokens.push_back({"Reserved word","continue"}),i+=7;
		else if(isdigit(code[i])){
			int cur=i;
			while(cur+1<code.size()&&isdigit(code[cur+1]))cur++;
			tokens.push_back({"Number",code.substr(i,cur-i+1)});
			i=cur;
		}
		else if(isidchar(code[i])){
			int cur=i;
			while(cur+1<code.size()&&isidchar(code[cur+1]))cur++;
			tokens.push_back({"Identifier",code.substr(i,cur-i+1)});
			i=cur;
		}
		else{
			cout<<"Invalid symbol: "<<code[i]<<"\n";
			return {};
		}
	}
	return tokens;
}
void PrintTree(vector<pair<token,vector<int>>> &tree,int idx=-1,string sp=""){
	if(idx==-1)idx+=tree.size();
	cout<<sp<<tree[idx].first.type<<" "<<tree[idx].first.text<<"\n";
	for(auto it:tree[idx].second)
		PrintTree(tree,it,sp+"    ");
	return;
}
vector<pair<token,vector<int>>> ParseTree(vector<token> inp){
	vector<pair<token,vector<int>>> tree;
	vector<int> cur;
	for(auto it:inp){
		cur.push_back(tree.size());
		tree.push_back({it,{}});
	}
	while(inp.size()&&(cur.size()>1||tree[cur[0]].first.type!="Code")){
		for(int i=0;i<cur.size();i++){
			for(int j=cur.size()-1;j>=i;j--){
				string next="lambda";
				if(j+1<cur.size())
					next=tree[cur[j+1]].first.type;
				if(next=="Symbol"||next=="Operator"||next=="Reserved word")
					next=tree[cur[j+1]].first.text;
				string prv="lambda";
				if(i)
					prv=tree[cur[i-1]].first.type;
				if(prv=="Symbol"||prv=="Operator"||prv=="Reserved word")
					prv=tree[cur[i-1]].first.text;
				string t="";
				for(int k=i;k<=j;k++){
					string s=tree[cur[k]].first.type;
					if(s=="Symbol"||s=="Operator"||s=="Reserved word")
						s=tree[cur[k]].first.text;
					t+=s;
				}
				string tar="";
				if(t=="StatementCode")
					tar="Code";
				else if(t=="Statement"&&(next=="lambda"||next=="}"))
					tar="Code";
				else if(t=="DatatypeIdentifier;"&&prv!="(")
					tar="Statement";
				else if(t=="DatatypeIdentifier=Expression;"&&prv!="(")
					tar="Statement";
				else if(t=="Identifier=Expression;"&&prv!="(")
					tar="Statement";
				else if(t=="input(Identifier);"&&prv!="(")
					tar="Statement";
				else if(t=="output(Expression);"&&prv!="(")
					tar="Statement";
				else if(t=="outputln(Expression);"&&prv!="(")
					tar="Statement";
				else if(t=="outputsp(Expression);"&&prv!="(")
					tar="Statement";
				else if(t=="{Code}")
					tar="Statement";
				else if(t=="{}")
					tar="Statement";
				else if(t=="if(Condition)Statement"&&(next!="else"))
					tar="Statement";
				else if(t=="if(Condition)StatementelseStatement")
					tar="Statement";
				else if(t=="for(forStatement;Condition;forStatement)Statement")
					tar="Statement";
				else if(t=="while(Condition)Statement")
					tar="Statement";
				else if(t=="break;")
					tar="Statement";
				else if(t=="continue;")
					tar="Statement";
				else if(t=="DatatypeIdentifier"&&next!="=")
					tar="forStatement";
				else if(t=="DatatypeIdentifier=Expression")
					tar="forStatement";
				else if(t=="Identifier=Expression"&&prv!="Datatype")
					tar="forStatement";
				else if(t=="input(Identifier)")
					tar="forStatement";
				else if(t=="output(Expression)")
					tar="forStatement";
				else if(t=="outputln(Expression)")
					tar="forStatement";
				else if(t=="outputsp(Expression)")
					tar="forStatement";
				else if(t=="int ")
					tar="Datatype";
				else if(t=="TermE")
					tar="Expression";
				else if(t=="Term"&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"))
					tar="Expression";
				else if(t=="+TermE")
					tar="E";
				else if(t=="+Term"&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"))
					tar="E";
				else if(t=="-TermE")
					tar="E";
				else if(t=="-Term"&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"))
					tar="E";
				else if(t=="FT")
					tar="Term";
				else if(t=="IdentifierT")
					tar="Term";
				else if((t=="F"||t=="Identifier")&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"||next=="+"||next=="-"||next=="E"))
					tar="Term";
				else if(t=="*FT"||t=="*IdentifierT")
					tar="T";
				else if((t=="*F"||t=="*Identifier")&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"||next=="+"||next=="-"||next=="E"))
					tar="T";
				else if(t=="/FT"||t=="/IdentifierT")
					tar="T";
				else if((t=="/F"||t=="/Identifier")&&(next=="lambda"||next==";"||next==")"||next=="||"||next=="&&"||next=="Comparator"||next=="+"||next=="-"||next=="E"))
					tar="T";
				else if(t=="(Expression)")
					tar="F";
				else if(t=="Number")
					tar="F";
				else if(t=="ExpressionComparatorExpression&&Condition")
					tar="Condition";
				else if(t=="ExpressionComparatorExpression||Condition")
					tar="Condition";
				else if(t=="ExpressionComparatorExpression"&&(next==")"||next==";"))
					tar="Condition";
				else if(t=="(Condition)"&&(prv!="while"&&prv!="for"&&prv!="if"))
					tar="Condition";
				if(tar!=""){
					vector<int> vec1,vec2;
					string x="";
					for(int k=0;k<cur.size();k++){
						if(k>=i&&k<=j){
							if(k==i)
								vec2.push_back(tree.size());
							vec1.push_back(cur[k]);
							x+=tree[cur[k]].first.text;
						}
						else
							vec2.push_back(cur[k]);
					}
					cur=vec2;
					tree.push_back({{tar,x},vec1});
					goto a;
				}
			}
		}
		break;
		a:;
	}
	if(cur.size()>1||tree[cur[0]].first.type!="Code"){
		cout<<"Invalid syntax\n";
		return {};
	}
	return tree;
}
set<string> var;
set<string> dvar[100];
bool semanticAnalysis(vector<pair<token,vector<int>>> &tree,int cur=-1,int cnt=0,bool dec=0,int d=0){
	if(cur==-1){
		cur+=tree.size();
		var.clear();
	}
	if(tree[cur].first.type=="Identifier"){
		bool fnd=dvar[d].find(tree[cur].first.text)!=dvar[d].end();
		var.insert(tree[cur].first.text);
		dvar[d].insert(tree[cur].first.text);
		return fnd!=dec;
	}
	dec=0;
	if(tree[cur].first.type=="Statement"||tree[cur].first.type=="forStatement"){
		if(tree[cur].first.text=="break;"||tree[cur].first.text=="continue;")
			return !!cnt;
		int a=tree[cur].second[0],b=tree[cur].second[1];
		if(tree[a].first.type=="Datatype")
			dec=1;
		else{
			if(tree[a].first.text=="for"||tree[a].first.text=="while")
				cnt++;
			if(tree[a].first.text=="for"||tree[a].first.text=="while"||tree[a].first.text=="if"||tree[a].first.text=="{"){
				d++;
				dvar[d]=dvar[d-1];
			}
		}
	}
	bool bol=1;
	for(auto it:tree[cur].second)
		bol&=semanticAnalysis(tree,it,cnt,dec,d);
	return bol;
}
string curlabel;
string nextLabel(string curlabel){
	bool bol=0;
	for(auto it:curlabel)
		bol|=it!='Z';
	if(!bol){
		curlabel+='A';
		for(auto &it:curlabel)
			it='A';
		return curlabel;
	}
	int i;
	for(i=curlabel.size()-1;curlabel[i]=='Z';i--)
		curlabel[i]='A';
	curlabel[i]++;
	return curlabel;
}
string convertCode(vector<pair<token,vector<int>>> &tree,int cur=-1,string endloop="",string continueloop="",string curCalc="",string fjump="",string tjump=""){
	string res="";
	if(cur==-1){
		curlabel="";
		cur+=tree.size();
	}
	if(tree[cur].first.type=="Statement"||tree[cur].first.type=="forStatement"){
		if(tree[cur].first.text[0]=='{')
			return res+=convertCode(tree,tree[cur].second[1],endloop,continueloop,curCalc);
		if(tree[cur].first.text=="break;")
			return res+="\tjmp __label"+endloop+"\n";
		if(tree[cur].first.text=="continue;")
			return res+="\tjmp __label"+continueloop+"\n";
		int a=tree[cur].second[0];
		if(tree[a].first.type=="Identifier"){
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			return res+=x+
			"\tmov ["+tree[a].first.text+"], eax\n";
		}
		if(tree[a].first.type=="Datatype"&&tree[cur].second.size()>3){
			string x=convertCode(tree,tree[cur].second[3],endloop,continueloop,curCalc);
			return res+=x+
			"\tmov ["+tree[tree[cur].second[1]].first.text+"], eax\n";
		}
		if(tree[a].first.text=="input")
			return res+=
			"\tmov rcx, formin\n\tmov rdx, "+
			tree[tree[cur].second[2]].first.text+"\n"+
			"\tcall scanf\n";
		if(tree[a].first.text=="output"){
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			return res+=x+
			"\tmov rcx, formout\n"+
			"\tmov edx, eax\n"+
			"\tcall printf\n";
		}
		if(tree[a].first.text=="outputln"){
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			return res+=x+
			"\tmov rcx, formoutln\n"+
			"\tmov edx, eax\n"+
			"\tcall printf\n";
		}
		if(tree[a].first.text=="outputsp"){
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			return res+=x+
			"\tmov rcx, formoutsp\n"+
			"\tmov edx, eax\n"+
			"\tcall printf\n";
		}
		if(tree[a].first.text=="if"){
			if(tree[cur].second.size()==7){
				curlabel=nextLabel(curlabel);
				string startif=curlabel;
				curlabel=nextLabel(curlabel);
				string endif=curlabel;
				curlabel=nextLabel(curlabel);
				string endelse=curlabel;
				string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc,endif,startif);
				string y=convertCode(tree,tree[cur].second[4],endloop,continueloop,curCalc);
				string z=convertCode(tree,tree[cur].second[6],endloop,continueloop,curCalc);
				return res+=x+
				"\t__label"+startif+": \n"+
				y+
				"\tjmp __label"+endelse+"\n"+
				"\t__label"+endif+":\n"+
				z+
				"\t__label"+endelse+":\n";
			}
			curlabel=nextLabel(curlabel);
			string startif=curlabel;
			curlabel=nextLabel(curlabel);
			string endif=curlabel;
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc,endif,startif);
			string y=convertCode(tree,tree[cur].second[4],endloop,continueloop,curCalc);
			return res+=x+
			"\t__label"+startif+": \n"+
			y+
			"\t__label"+endif+":\n";
		}
		if(tree[a].first.text=="while"){
			curlabel=nextLabel(curlabel);
			string continuewhile=curlabel;
			curlabel=nextLabel(curlabel);
			string startwhile=curlabel;
			curlabel=nextLabel(curlabel);
			string endwhile=curlabel;
			string x=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc,endwhile,startwhile);
			string y=convertCode(tree,tree[cur].second[4],endwhile,continuewhile);
			return res+="\t__label"+continuewhile+":\n"+
			x+
			"\t__label"+startwhile+": \n"+
			y+
			"\tjmp __label"+continuewhile+"\n"+
			"\t__label"+endwhile+":\n";
		}
		if(tree[a].first.text=="for"){
			curlabel=nextLabel(curlabel);
			string startfor=curlabel;
			curlabel=nextLabel(curlabel);
			string startbody=curlabel;
			curlabel=nextLabel(curlabel);
			string continuefor=curlabel;
			curlabel=nextLabel(curlabel);
			string endfor=curlabel;
			string s1=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			string con=convertCode(tree,tree[cur].second[4],endloop,continueloop,curCalc,endfor,startbody);
			string s2=convertCode(tree,tree[cur].second[6],endloop,continueloop,curCalc);
			string body=convertCode(tree,tree[cur].second[8],endfor,continuefor);
			return res+=s1+
			"\t__label"+startfor+":\n"+
			con+
			"\t__label"+startbody+":\n"+
			body+
			"\t__label"+continuefor+": \n"+
			s2+
			"\tjmp __label"+startfor+"\n"+
			"\t__label"+endfor+":\n";
		}
		return "";
	}
	if(tree[cur].first.type=="Expression"){
		if(tree[cur].second.size()==1)
			return res+=convertCode(tree,tree[cur].second[0],endloop,continueloop,curCalc);
		string x=convertCode(tree,tree[cur].second[0],endloop,continueloop,curCalc);
		string y=convertCode(tree,tree[cur].second[1],endloop,continueloop,curCalc);
		return res+=x+y;
	}
	if(tree[cur].first.type=="Term"){
		string x=convertCode(tree,tree[cur].second[0],endloop,continueloop,curCalc);
		string y="";
		if(tree[cur].second.size()==2)
			y=convertCode(tree,tree[cur].second[1],endloop,continueloop,curCalc);
		return res+=x+y;
	}
	if(tree[cur].first.type=="T"){
		curCalc=nextLabel(curCalc);
		var.insert("__temporaryCalc"+curCalc);
		string z="";
		if(tree[cur].second.size()>2)
			z=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
		string x=convertCode(tree,tree[cur].second[1],endloop,continueloop,curCalc);
		if(tree[cur].first.text[0]=='*'){
			return res+="\tmov [__temporaryCalc"+curCalc+"], eax\n"+
			x+
			"\timul eax, [__temporaryCalc"+curCalc+"]\n"+
			z;
		}
		return res+="\tmov [__temporaryCalc"+curCalc+"], eax\n"+
		x+
		"\tmov ebx, [__temporaryCalc"+curCalc+"]\n"+
		"\tmov ecx, eax\n"+
		"\tmov eax, ebx\n"+
		"\tmov edx, 0\n"+
		"\tidiv ecx\n"+
		z;
	}
	if(tree[cur].first.type=="E"){
		curCalc=nextLabel(curCalc);
		var.insert("__temporaryCalc"+curCalc);
		string z="";
		if(tree[cur].second.size()>2)
			z=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
		string x=convertCode(tree,tree[cur].second[1],endloop,continueloop,curCalc);
		return res+="\tmov [__temporaryCalc"+curCalc+"], eax\n"+
		x+
		(tree[cur].first.text[0]=='+'?"\tadd eax, [__temporaryCalc":"\tsub eax, [__temporaryCalc")+curCalc+"]\n"+
		(tree[cur].first.text[0]=='+'?"":"\tneg eax\n")+
		z;
	}
	if(tree[cur].first.type=="Identifier")
		return res+="\tmov eax, ["+tree[cur].first.text+"]\n";
	if(tree[cur].first.type=="F")
		return res+=convertCode(tree,tree[cur].second[tree[cur].second.size()/2],endloop,continueloop,curCalc);
	if(tree[cur].first.type=="Number")
		return res+="\tmov eax, "+tree[cur].first.text+"\n";
	if(tree[cur].first.type=="Condition"){
		if(tree[cur].second.size()==3){
			curCalc=nextLabel(curCalc);
			var.insert("__temporaryCompare"+curCalc);
			string x=convertCode(tree,tree[cur].second[0],endloop,continueloop,curCalc);
			string y=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			string j="",com=tree[tree[cur].second[1]].first.text;
			if(com=="==")
				j="je";
			else if(com=="!=")
				j="jne";
			else if(com==">")
				j="jg";
			else if(com==">=")
				j="jge";
			else if(com=="<")
				j="jl";
			else
				j="jle";
			return res+=y+
			"\tmov [__temporaryCompare"+curCalc+"], eax\n"+
			x+
			"\tcmp eax, [__temporaryCompare"+curCalc+"]\n"+
			"\t"+j+" __label"+tjump+"\n"+
			"\tjmp __label"+fjump+"\n";
		}
		else{
			curCalc=nextLabel(curCalc);
			var.insert("__temporaryCompare"+curCalc);
			string x=convertCode(tree,tree[cur].second[0],endloop,continueloop,curCalc);
			string y=convertCode(tree,tree[cur].second[2],endloop,continueloop,curCalc);
			string zz=tree[tree[cur].second[3]].first.text;
			string z=convertCode(tree,tree[cur].second[4],endloop,continueloop,curCalc,fjump,tjump);
			string j="",com=tree[tree[cur].second[1]].first.text;
			if(zz=="&&"){
				if(com=="!=")
					j="je";
				else if(com=="==")
					j="jne";
				else if(com=="<=")
					j="jg";
				else if(com=="<")
					j="jge";
				else if(com==">=")
					j="jl";
				else
					j="jle";
				return res+=y+
				"\tmov [__temporaryCompare"+curCalc+"], eax\n"+
				x+
				"\tcmp eax, [__temporaryCompare"+curCalc+"]\n"+
				"\t"+j+" __label"+fjump+"\n"+
				z;
			}
			else{
				if(com=="==")
					j="je";
				else if(com=="!=")
					j="jne";
				else if(com==">")
					j="jg";
				else if(com==">=")
					j="jge";
				else if(com=="<")
					j="jl";
				else
					j="jle";
				return res+=y+
				"\tmov [__temporaryCompare"+curCalc+"], eax\n"+
				x+
				"\tcmp eax, [__temporaryCompare"+curCalc+"]\n"+
				"\t"+j+" __label"+tjump+"\n"+
				z;
			}
		}
	}
	if(tree[cur].first.type=="Code"){
		for(auto it:tree[cur].second)
			res+=convertCode(tree,it,endloop,continueloop,curCalc);
	}
	if(cur==tree.size()-1){
		res+="\txor ecx, ecx\n\tcall ExitProcess\n";
	}
	return res;
}

int main(){
	string code=readCode();
	// cout<<code<<"\n\n\n";
	vector<token> tokens=LexicalAnalysis(code);
	// PrintTokens(tokens);
	// cout<<"\n\n\n";
	if(tokens.empty()){
		return 0;
	}
	vector<pair<token,vector<int>>> tree=ParseTree(tokens);
	if(tree.empty())
		return 0;
	// PrintTree(tree);
	// cout<<"\n\n\n";
	bool bol=semanticAnalysis(tree);
	if(!bol){
		cout<<"Semantic Analysis Failed\n";
		return 0;
	}
	// cout<<(bol?"Semantic Analysis Passed\n":"Semantic Analysis Failed\n");
	// cout<<"\n\n\n";
	string assembly=convertCode(tree);
	string res="";
	res+="bits 64\ndefault rel\nextern printf\nextern scanf\nextern ExitProcess\nsection .data\n\tformin db \"%d\", 0\n\tformout db \"%d\", 0\n\tformoutsp db \"%d\", 32, 0\n\tformoutln db \"%d\", 10, 0\nsection .bss\n";
	for(auto it:var)
		res+="\t"+it+" resd 1\n";
	res+="section .text\nglobal main\nmain:\n";
	res+=assembly;
	cout<<res<<"\n";
    return 0;
}