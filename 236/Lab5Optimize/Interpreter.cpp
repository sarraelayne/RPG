#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram var){
    //Store the DatalogProgram as a data member
    dp = var;  
    //Make a Relation for each scheme Predicate, and put that Relation in the Database data member; database is a map<string, Relation>
    vector<Predicate> sch = dp.getSchemes();
    for(unsigned i = 0; i < sch.size(); i++){
        string name = sch.at(i).getPredicateID();
        Scheme data;
        data.push_back(sch.at(i).getPredicateParameter());
        vector<string> myParams = sch.at(i).getPredicateParameterList();
        for(unsigned i = 0; i < myParams.size(); i++){
            if(myParams.at(i) != ","){
                data.push_back(myParams.at(i));
            }
        }
        Relation temp = Relation(name, data);
        Scheme resultScheme = temp.getScheme();
        db.insert(pair<string, Relation> (name, temp));
    }
    
    //Make a Tuple for each fact Predicate, and put that Tuple in the appropriate Relation in the Database
    vector<Predicate> facts = dp.getFacts();
    for(unsigned i = 0; i < facts.size(); i++){
        string name = facts.at(i).getPredicateID();
        Tuple data;
        data.push_back(facts.at(i).getPredicateParameter());
        vector<string> myParams = facts.at(i).getPredicateParameterList();
        for(unsigned i = 0; i < myParams.size(); i++){
            if(myParams.at(i) != ","){
                data.push_back(myParams.at(i));
            }
        }
        //find Relation in map and insert tuple
        Relation temp;
        std::map<string,Relation>::iterator it;
        it = db.find(name);
        it->second.addTuple(data);
    }
    db.databaseToString();
}
Interpreter::~Interpreter(){}


Relation Interpreter::evalQuery(Predicate queryPredicate){
    //Make a function in the Interpreter that evaluates one query predicate and returns a relation
    string name = queryPredicate.getPredicateID();
    vector<string> queryData;
    queryData.push_back(queryPredicate.getPredicateParameter());
    vector<string> queryParams = queryPredicate.getPredicateParameterList();
    
    for(unsigned i = 0; i < queryParams.size(); i++){
        if(queryParams.at(i) != ","){
            queryData.push_back(queryParams.at(i));
        }
    }
    
    //Grab the corresponding Relation from the Database
    Relation dbRel = db.find(name)->second; //map<string, Relation>  
    Scheme dbRelScheme;
    
    //Go through the parameters: For each Parameter:
    map<string, int> colToKeep;
    vector<int> CTKvec;
    vector<string> renameValues;
    for(unsigned int i = 0; i < queryData.size();i++){ 
    //1: Constant or Variable? parse for const, variable, or expression
        string currStr = queryData.at(i);
        if(currStr.at(0) == '\''){//is Constant
            dbRel = dbRel.select1(i, currStr);
        }
        else{//is variable
            map<string, int>::iterator it = colToKeep.find(currStr);
            if(it!=colToKeep.end()){//if seen it before
                cout << "pre find\n";
                int firstSpot = colToKeep.find(currStr)->second;
                dbRel = dbRel.select2(firstSpot, i);
            }
            else{//haven't seen it before
                int commaCounter = 0;
                if(currStr != ","){
                    colToKeep.insert(std::pair<string, int>(currStr,i));
                    CTKvec.push_back(i);
                    renameValues.push_back(currStr);
                }
                else{
                    cout << "Found a comma! interpreter evalQuery\n";
                    commaCounter++;
                }
            }
        }
    }

    //Do one whole project: need vector<int> of columns to keep
    dbRel = dbRel.project(CTKvec);
    dbRelScheme.clear();
    for(unsigned int i = 0; i < renameValues.size();i++){
        dbRelScheme.push_back(renameValues.at(i));
    }
    dbRel.setScheme(dbRelScheme);
    Scheme relSche = dbRel.getScheme();

    return dbRel;
}
void Interpreter::evalAllQueries(){
    //vector of queries, cycle through and evaluate
    vector<Predicate> queries = dp.getQueries();
    for(unsigned i = 0; i < queries.size(); i++){
        queryResults.push_back(evalQuery(queries.at(i)));
    }
    for(unsigned i = 0; i < queries.size();i++){ 
        cout << queries.at(i).predicateToString();
        string name = queries.at(i).getPredicateID(); 
        Relation tempResult = queryResults.at(i);
        int tupSetSize = tempResult.getTupSetSize();
        if(tupSetSize > 0){
            cout << " Yes(" << tupSetSize << ")" << endl;
            queryResults.at(i).relationToString();
        }
        else{
            cout << " No" << endl;
        }
    }
}
Relation Interpreter::evalRule(Rule ruleObj){//add tuples to database, maybe could be void, queryeval(predicates) on RHS to get relations
    //Make a function in the Interpreter that evaluates one query predicate and returns a relation
    cout << ruleObj.ruleToString() << endl;
    
    //1: Evaluate the predicates on the rhs of the Rule////////////////////////////////
    string ruleHeadPred = ruleObj.getRuleHeadPredicate(); 
    Predicate headPred = this->parseRulePredicate(ruleHeadPred);
    string rulePred = ruleObj.getRulePredicate();
    Predicate pred = this->parseRulePredicate(rulePred);
    vector<string> rulePredList = ruleObj.getRulePredicateList();
    vector<string> ruleColToProject;//for part 3
    ruleColToProject.push_back(ruleHeadPred);
    
    vector<string> ruleCTP2;//for part 3
    for(unsigned int y = 0; y < ruleColToProject.size(); y++){
        bool hitParen = false;
        string val = ruleColToProject.at(y);
        string combine;
        for(unsigned int p = 0; p < val.length(); p++){
            if(val.at(p) == '('){
                hitParen = true;
            }
            else if(val.at(p) == ')'){
                hitParen = false;
            }
            else if(hitParen){
                string temp = string(1, val.at(p));
                unsigned int num = val.length()-1;
                if(temp == ","){}
                else if(p < num){
                    if(val.at(p+1) != ',' && val.at(p+1) != ')'){
                        combine.append(temp);
                    }
                    else if(val.at(p) != ','){
                        combine.append(temp);
                        ruleCTP2.push_back(combine);
                        combine = "";
                    }
                }
                else{
            
                }
            }
        }
    }
    vector<Predicate> predList;
    predList.push_back(pred);
    for(unsigned int f = 0; f < rulePredList.size(); f++){
        string temp = rulePredList.at(f);
        if(isalpha(temp[0])){
            predList.push_back(this->parseRulePredicate(rulePredList.at(f)));
        }
    }
    vector<Relation> rhs;
    for(unsigned int q = 0; q < predList.size();q++){
        Relation temp = evalQuery(predList.at(q));
        rhs.push_back(temp);
    }
    
    //2: Join the Relations that result /////////////////////////////
    Relation result;
    vector<Relation> results;
    for(unsigned int z = 0; z < rhs.size(); z++){
        Relation temp = rhs.at(z);
        if(z == 0){
            results.push_back(temp);
        }
        else{
            Relation partialAnswer = results.at(z-1).join(temp);
            results.push_back(partialAnswer);
        }
    }
    
    Relation result2 = results.at(results.size()-1);

    //3: Project the columns that appear in the head predicate = predicates of the Rule object//////////////////////////
    vector<int> projectMe;
    Scheme resScheme = result2.getScheme();

    for(unsigned int u = 0; u < ruleCTP2.size();u++){ 
        string temp = ruleCTP2.at(u);
        for(unsigned int e = 0; e < resScheme.size(); e++){
            if(resScheme.at(e) == temp){
                projectMe.push_back(e);
            }
        }
    }
    Relation result3 = result2.project(projectMe);
    
    //4: Rename the Relation to make it union-compatible
    //find matching name in database, get that scheme, rename your scheme to that
    string IDname = headPred.getPredicateID();
    Relation dbRel = db.find(IDname)->second; //access elements from a map
    Scheme dbRelScheme = dbRel.getScheme();
    result3.setScheme(dbRelScheme);

    //5: Union with the Relation in the database
    Relation dbRel2 = db.find(IDname)->second;
    Relation result4 = result3.unionRelations(dbRel2);
    db[IDname] = result4;

    return result4;
}
//************************************************************************************************************************************************************
Predicate Interpreter::parseRulePredicate(string predicate){
    Predicate result = Predicate("ir");
    string head;
    unsigned int marker = 999999;
    string parameter;
    string compVal;
    for(unsigned int u = 0; u<predicate.length();u++){
        if(predicate.at(u) != '(' && u < marker && predicate.at(u)!= ','){
            head.push_back(predicate.at(u));
        }
        else if(predicate.at(u) == '('){
            marker = u;
        }
        else if(predicate.at(u) == ','){
        }
        else if(predicate.at(u) != '(' && predicate.at(u) != ')' && predicate.at(u) != ',' && parameter == "" && predicate.at(u)!= ','){
            if(u < predicate.length()-1){
                if(predicate.at(u+1) != ',' && predicate.at(u+1) != ')'){
                    compVal.push_back(predicate.at(u));
                }
                else{
                    compVal.push_back(predicate.at(u));
                    parameter.append(compVal);
                    compVal = "";
                }
            }
        }
        else if(predicate.at(u) != '(' && predicate.at(u) != ')' && predicate.at(u) != ',' && parameter != "" && predicate.at(u)!= ','){
            string tempPred;
            
            if(u < predicate.length()-1){
                if(predicate.at(u+1) != ',' && predicate.at(u+1) != ')'){
                    compVal.push_back(predicate.at(u));
                }
                else{
                    compVal.push_back(predicate.at(u));
                    tempPred.append(compVal);
                    result.updatePredicateParameterList(tempPred);
                    compVal = "";
                }
            }
        }
    }
    result.updatePredicateID(head);
    result.updatePredicateParameter(parameter);

    return result;
}
void Interpreter::evalAllRules(){//fixed point algorithm, check if tuples added
    //cycle through all the rules
    vector<Rule> rules = dp.getRules();
    
    
    //Fixed-Point Algorithm
    unsigned int precount = db.countTuples();
    unsigned int postcount = 99999;
    unsigned int loopCount = 0;
    while(precount != postcount){
        precount = db.countTuples();
        for(unsigned i = 0; i < rules.size(); i++){
            ruleResults.push_back(evalRule(rules.at(i)));
        }
        postcount = db.countTuples();
        loopCount++;
    }
    
    cout << "\nSchemes populated after " << loopCount << " passes through the Rules.\n";
}