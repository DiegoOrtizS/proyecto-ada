struct node{
    int id;
    int pos;

    map<char,node*> adj;
    node(int pos){
        this->pos=pos;
    }
};
node* build_trie(int i, int j, matriz &min_pos);

void printTrieGen(node* root);

node* completeBuild(int i,int j, matriz &min_pos);

vector<string> executeQuery(node* root, string query);


void executeQuery(node* root, string query, vector<char> &rpta, char* cumple){
    if (root->pos == -1) 
    {
        // if (!strcmp(cumple, ""))
        if (cumple != nullptr)
            rpta.push_back(*cumple);
        return;
    }

    if (query[root->pos] == 'X')
    {
        for (auto it : root->adj)
        {   
            cumple = new char[1];
            *cumple= it.first; 
        
            executeQuery(it.second, query, rpta, cumple);
        }
    }
    else
    {
        if (root->adj.find(query[root->pos]) == root->adj.end()) return;
        executeQuery(root->adj[query[root->pos]], query, rpta, cumple);
    }
}


node* completeBuild(int i,int j, matriz &min_pos){

    node* root = build_trie(i,j,min_pos);
    auto ktp=K(i, j);
    // //uno con los ks
    for (int i=0;i<ktp.size();i++){
         node* tmp=new node(ktp[i]);
         char chartmp= S[0][ktp[i]];
         tmp->pos=ktp[i];
         tmp->adj[chartmp]=root;
         root=tmp;
    }
    return root;
}


node* build_trie(int i, int j, matriz &min_pos){
    if (i == j) {
        //Aqui devolverían un nodo 'terminal'
        return new node(-1);
    }

    int p = min_pos[i][j];
    auto c = C(i, j, p);

    //cambiar con la tabla de Ks para reducir la compeljidad
    auto r = R(i, j, K(i,j));
    int index = 1;

    node* root = new node(p);

    for (auto par : c) {
        node* newNode = build_trie(par.first, par.second, min_pos); 
        auto rp = R(par.first, par.second, K(par.first, par.second));

        vector<int> difR;
        //Acuerdense que para que este metodo funcione r y rp tienen que estar ordenados
        set_difference(r.begin(), r.end(), rp.begin(), rp.end(), back_inserter(difR)); //O(m)

        for (auto pp : difR) {
          if (pp == p) continue;
          node* temp = new node(pp);
          temp->adj[S[par.second - 1][pp]] = newNode;
          newNode = temp;
       }
       root->adj[S[par.second-1][p]] = newNode;
    }
    return root;
}

void printTrieGen(node* root){
    queue<node*>Q;
    Q.push(root);
    
    while(!Q.empty()){
        node* u = Q.front();
        Q.pop();
        if(!u->adj.empty()){
            cout << u->pos << " " << endl;
            for(auto it : u->adj)
            {
                Q.push(it.second);
                cout << it.first << ":"<< it.second->pos << " " << endl;
            }
            
        }
    }
};