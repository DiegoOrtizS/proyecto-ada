struct node{
    int id;
    int pos;
    map<char,node*> adj;
};
node* build_trie(int i, int j, matriz &min_pos);

void printTrieGen(node* root);

node* completeBuild(int i,int j, matriz &min_pos);


node* completeBuild(int i,int j, matriz &min_pos){

    node* root = build_trie(i,j,min_pos);
    auto ktp=K(i, j);
    // //uno con los ks
    for (int i=0;i<ktp.size();i++){
         node* tmp=new node{};
         char chartmp= S[0][ktp[i]];
         tmp->pos=ktp[i];
         tmp->adj[chartmp]=root;
         root=tmp;
    }
    return root;
}


node* build_trie(int i, int j, matriz &min_pos){
    int p = min_pos[i][j];
    auto c = C(i,j,p);
    //cambiar con la tabla de Ks para reducir la compeljidad
    auto r = R(i,j, K(i,j));
    int index = 1;
    node* root = new node{};
    root->pos = p;
    root->id = index;
    //root->isleaf=false;
    //1,1
    if(i==j){
        return root;
    }

    for (auto par : c)
    {
        auto rp = R(par.first,par.second,K(par.first, par.second));
        node* newNode = build_trie(par.first,par.second, min_pos); 
        vector<int> difR;
        vector<int> difP;
        difP.push_back(p);
        set_difference(r.begin(), r.end(),difP.begin(),difP.end(), back_inserter(difR)); //O(m)
    
        if(difR.size()>0){
            newNode->pos=difR[0];
        }

        auto temp= newNode;
        if(rp.size()==0){
            for (auto pp : difR)
            {
                if(pp == p)
                    continue;
                node* nodeP = new node{};
                nodeP->pos = -1;
                nodeP->id = ++index;
                newNode->adj[S[par.second-1][pp]] = nodeP;
                newNode = nodeP;

            }
        }

        root->adj[S[par.second-1][p]] = temp;        
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