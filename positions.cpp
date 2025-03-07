

void setVectorPositions(std::vector<int*>* vec, int* pos1, int* pos2){
    if (pos1[0] == pos2[0]){//vertical
        int lastPos = std::max(pos1[1], pos2[1]);
        int startPos = std::min(pos1[1], pos2[1]);

        for (int i = startPos; i <= lastPos; i++){
            int* posN = (int*)malloc(sizeof(int) * 2);
            posN[0] = pos1[0]; posN[1] = i;
            (*vec).insert((*vec).begin(), posN);
        }
    }
    else if (pos1[1] == pos2[1]){//horizontal
        int lastPos = std::max(pos1[0], pos2[0]);
        int startPos = std::min(pos1[0], pos2[0]);

        for (int i = startPos; i <= lastPos; i++){
            int* posN = (int*)malloc(sizeof(int) * 2);
            posN[0] = i; posN[1] = pos1[1];
            (*vec).insert((*vec).begin(), posN);
        }
    }
}