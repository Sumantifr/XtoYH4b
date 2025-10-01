#include <xgboost/c_api.h>
#include <iostream>
#include <vector>

int main() {
    BoosterHandle booster;
    const char* model_path = "../../MVA/Models/bdt_model.json";

    if (XGBoosterCreate(nullptr, 0, &booster) != 0 ||
        XGBoosterLoadModel(booster, model_path) != 0) {
        std::cerr << "Failed to load model." << std::endl;
        return 1;
    }

    std::vector<float> input_features = {0.1,0.1,1.,0.5,0.01,0.01,1.5,0.1,0.1,1.,0.5,0.01,0.01,1.5,0.25,2.,0.15,1.4,1000.,200.};
    DMatrixHandle dmat;
    XGDMatrixCreateFromMat(input_features.data(), 1, input_features.size(), -1, &dmat);

    bst_ulong out_len;
    const float* out_result = nullptr;
    int option_mask = 0;       // default: normal prediction
    unsigned ntree_limit = 0;  // 0 = use all trees
    int training = 0;
    XGBoosterPredict(booster, dmat, option_mask, ntree_limit, training, &out_len, &out_result);
    //XGBoosterPredict(booster, dmat, 0, 0, &out_len, &out_result);
    std::cout << "Prediction score: " << out_result[0] << std::endl;

    XGBoosterFree(booster);
    XGDMatrixFree(dmat);
    return 0;
}

