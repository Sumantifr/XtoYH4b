#include <cstdio>
#include <iostream>
#include "correction.h"

using namespace correction;
using namespace std;

int main()
{
auto cset = CorrectionSet::from_file("btagging.json.gz");
for (auto& corr : *cset) {
    cout<<"Correction: "<<corr.first.c_str()<<endl;;
}
auto pnet = cset->at("particleNet_shape");
double out = pnet->evaluate({"central", 0, 1.2, 35., 1.00});
cout<<"SF "<<out<<endl;
}
