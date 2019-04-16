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
    //1: EVALUATE PREDICATES ON RHS OF RULE
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
    
    //2: JOIN RESULTING RELATIONS
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

    //3: Project the columns that appear in the head predicate = predicates of the Rule object
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
    /*cout << endl << "result3: ";
    result3.relationToString();
    cout << endl << endl;*/
    
    //4: RENAME RELATION SO IT CAN BE UNIONED
    //find matching name in database, get that scheme, rename your scheme to that
    string IDname = headPred.getPredicateID();
    Relation dbRel = db.find(IDname)->second; //access elements from a map
    Scheme dbRelScheme = dbRel.getScheme();
    result3.setScheme(dbRelScheme);

    //5: UNION WITH THE RELATION IN THE DATABASE
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
void Interpreter::evalAllRules(vector<int> comps){//fixed point algorithm, check if tuples added THiS IS WHERE IT GETS WEIRD PRINTING LAB5
    //cycle through all the rules
    vector<Rule> rules = dp.getRules();
    vector<Rule> sccRules;
    
    for(unsigned int i = 0; i < comps.size(); i++) {
        sccRules.push_back(rules.at(comps[i]));
    }
    
    //Fixed-Point Algorithm
    unsigned int precount = db.countTuples();
    unsigned int postcount = 99999;
    unsigned int loopCount = 0;
    while(precount != postcount){
        precount = db.countTuples();
        for(unsigned i = 0; i < sccRules.size(); i++){
            ruleResults.push_back(evalRule(sccRules.at(i)));
        }
        postcount = db.countTuples();
        loopCount++;
        numPasses++;
    }
    //numPasses++;
    //cout << loopCount << " passes: R";
    //cout << "\nSchemes populated after " << loopCount << " passes through the Rules.\n";
}
bool Interpreter::isRuleDependent(Rule rule1, Rule rule2) {
    /*for (unsigned int i = 0; i < rule2.getRulePredicateList().size(); i++) {
        cout << "predicate: " << rule2.getRulePredicateList().at(i) << endl;
    }*/
    string rule1String = rule1.getRuleHeadPredicate().substr(0, rule1.getRuleHeadPredicate().find("("));
    string rule2String = rule2.getRulePredicate().substr(0, rule2.getRulePredicate().find("("));
    //cout << "rule1: " << rule1String << endl;
    //cout << "rule2: " << rule2String << endl;
    if (rule1String == rule2String) {
        return true;
    }
    for (unsigned int i = 0; i < rule2.getRulePredicateList().size(); i++) {
        
        if (rule2.getRulePredicateList().at(i) == ",") continue;
        //cout << "predicate: " << rule2.getRulePredicateList().at(i) << endl;
        string ruleForString = rule2.getRulePredicateList().at(i).substr(0, rule2.getRulePredicateList().at(i).find("("));
        //cout << "ruleFS: " << ruleForString << endl;
        if (rule1String == ruleForString) { //checking the comma? Rule 2 is staying constant
        //grab head of rule, check all predicates in the list against head predicate. If match then add. 
            return true;
        }
    }
    //cout << "after for" << endl;
    return false;
}
void Interpreter::smartEvalRules() {
    vector<Rule> rules = dp.getRules();
    unsigned int nRules = rules.size();
    graph dependency = graph(nRules);
    for (unsigned int i = 0; i < nRules; i++) {
        //cout << "Rules: " << endl;
        //cout << rules[i].ruleToString() << endl;
        for (unsigned int j = 0; j < nRules; j++) {
            //if(i == j) continue;
            //cout << "i: " << i << " j: " << j << endl;
            if (isRuleDependent(rules[i],rules[j])) {
                //cout << "found edge" << endl;
                dependency.addEdge(j, i);
            }
        }
    }

    //OUTPUT DEPENDENCY GRAPH
    cout << "Dependency Graph" << endl;
    //cout << "Reverse Graph" << endl;
    graph rg = dependency.reverse();
    //cout << rg.toString() << endl;
    vector<int> pnums = rg.DFSForest();
    //cout << "Postorder Numbers"  << endl;
    //cout << rg.positions() << endl;
    //cout << "SCC Search Order" << endl;*/
    cout << dependency.toString(); //extra comma
    cout << endl;
    
    cout << "Rule Evaluation" << endl;
    vector<vector<int>> comps = dependency.scc();
    //numPasses = 0;
    for (unsigned int i = 0; i < comps.size(); i++) {
        numPasses = 0;
        cout << "SCC: ";
        unsigned int compSize = comps[i].size();
        //cout << "compSize: " << compSize << endl;
        for (unsigned int j = 0; j < compSize; j++) {
            cout << "R" << comps[i][j];
            if(compSize > 1 && j < compSize - 1) {
                cout << ",";
            }
        }
        cout << endl;
        if (compSize == 1 && !dependency.hasEdge(comps[i][0], comps[i][0])) { ////dependency.nodeVec[i].neighbors.empty();
            evalRule(rules[comps[i][0]]);
            numPasses++;
            //cout << endl;
            //numPasses++; 
            //cout << "RULES: " << rules[comps[i][0]].ruleToString() << endl;
        }
        else {
            //cout << "compi:" << comps[i].at(0) << endl;
            evalAllRules(comps[i]);
        }
        //print out all comps[i][0], , , 
        cout << numPasses << " passes: ";
        for (unsigned int k = 0; k < comps[i].size(); k++) {
            cout << "R" << comps[i][k];
            if (k < comps[i].size() - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
}
void Interpreter::printRules(unsigned int nRules, vector<int> pnums) {
    for (unsigned int i = 0; i < nRules; i++) {
        cout << "R" << i << ":"; //<< pnums[i] << endl;
        /*for(unsigned j = 0; j < pnums.size(); j++){
            cout << "R" << pnums.at(j) << endl;
        }*/
        cout << "R" << pnums[nRules -i] << endl;
    }
}