#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define MAX 500003

int *arr = new int[MAX]; 

struct node
{
    ll maxi,lmaxi,rmaxi,sum;
}tree[4*MAX+10];

void pushup(int rt)
{
    tree[rt].sum = tree[2*rt].sum + tree[2*rt+1].sum;
    tree[rt].maxi = max(tree[2*rt].maxi,max(tree[2*rt+1].maxi,tree[2*rt].rmaxi+tree[2*rt+1].lmaxi));
    tree[rt].lmaxi = max(tree[2*rt].lmaxi,tree[2*rt].sum + tree[2*rt+1].lmaxi);
    tree[rt].rmaxi = max(tree[2*rt+1].rmaxi,tree[2*rt+1].sum + tree[2*rt].rmaxi);
}

void build(int l,int r,int rt)
{
    if(l == r)
    {
    	tree[rt].sum = arr[l];
        tree[rt].maxi = tree[rt].lmaxi = tree[rt].rmaxi = tree[rt].sum;
        return;
    }
    int mid = (l+r)/2;
    build(l,mid,2*rt);
    build(mid+1,r,2*rt+1);
    pushup(rt);
}

void update(int l,int r,int pos,int val,int rt)
{
    if(l == r)
    {
        tree[rt].maxi = tree[rt].lmaxi = tree[rt].rmaxi = tree[rt].sum = val;
        return;
    }
    int mid = (l+r)/2;
    if(pos <= mid)
        update(l,mid,pos,val,2*rt);
    else
        update(mid+1,r,pos,val,2*rt+1);
    pushup(rt);
}

node query(int l,int r,int aa,int bb,int rt)
{
    if(aa <= l && bb >= r)
        return tree[rt];
    int mid = (l+r)/2;
    node ka,kb,res;
    int flag1 = 0;
    int flag2 = 0;
    if(aa <= mid)
    {
        ka = query(l,mid,aa,bb,2*rt);
        flag1 = 1;
    }
    if(bb > mid)
    {
        kb = query(mid+1,r,aa,bb,2*rt+1);
        flag2 = 1;
    }
    if(flag1 && flag2)
    {
        res.sum = ka.sum + kb.sum;
        res.lmaxi = max(ka.lmaxi,ka.sum+kb.lmaxi);
        res.rmaxi = max(kb.rmaxi,kb.sum+ka.rmaxi);
        res.maxi = max(ka.rmaxi+kb.lmaxi,max(ka.maxi,kb.maxi));
    }
    else
    {
        if(flag1)  //left
            res = ka;
        else
            res = kb;
    }
    return res;
}

int main() {
	
	int n,q;
	cin >> n; 
	cin >> q;
	for (int i=0; i<n; i++) {
		cin >> arr[i+1];
	} 
	build(1,n,1);
	node res;
	int pos,val;
	for (int i=0; i < q; i++) {
		res = query(1,n,1,n,1);
		if (res.maxi < 0) 
			cout << 0 << endl;
		else 
			cout << res.maxi << endl;
		cin >> pos >> val;
		update(1,n,pos,val,1);
	}
	res = query(1,n,1,n,1);
	if (res.maxi < 0) 
		cout << 0 << endl;
	else 
		cout << res.maxi << endl;

	return 0;
}

