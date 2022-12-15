#include <Arduino.h>
#include "string.h"

typedef unsigned int (*action0)(void);
typedef unsigned int (*action1)(unsigned int);
typedef unsigned int (*action2)(unsigned int, unsigned int);
typedef unsigned int (*action3)(unsigned int, unsigned int, unsigned int);
typedef unsigned int (*action4)(unsigned int, unsigned int, unsigned int, unsigned int);
#define ACTION_N(n) action##n
#define N_PARAM0(paramArr) ()
#define N_PARAM1(paramArr) (paramArr[0])
#define N_PARAM2(paramArr) (paramArr[0], paramArr[1])
#define N_PARAM3(paramArr) (paramArr[0], paramArr[1], paramArr[2])
#define N_PARAM4(paramArr) (paramArr[0], paramArr[1], paramArr[2], paramArr[3])
#define N_PARAM(n, paramArr) N_PARAM##n(paramArr)
#define callAction(n, action, paramArr) ({ \
    unsigned int ret = (unsigned int)0; \
    switch(n){ \
        case 0: \
        ret = ((ACTION_N(0))action)N_PARAM(0, paramArr); \
        break; \
        case 1: \
        ret = ((ACTION_N(1))action)N_PARAM(1, paramArr); \
        break; \
        case 2: \
        ret = ((ACTION_N(2))action)N_PARAM(2, paramArr); \
        break; \
        case 3: \
        ret = ((ACTION_N(3))action)N_PARAM(3, paramArr); \
        break; \
        case 4: \
        ret = ((ACTION_N(4))action)N_PARAM(4, paramArr); \
        break; \
    } \
    ret; \
})

extern unsigned int a, b, c, d, e, f;
extern void* actionTable[];

#define GET_CONDITION_VAR(n) ( \
    n==10?a:( \
        n==11?b:( \
            n==12?c:( \
                n==13?(unsigned int)d: ( \
                    n==14?e: f )))))

#define SET_CONDITION_VAR(n, v) ( \
    n==10?(a=v):( \
        n==11?(b=v):( \
            n==12?(c=v):( \
                n==13? (unsigned int)(d=v):( \
                    n==14?(e=v):(1?(f=v):0U))))))

char rawCodingTable[] = "1 0 0";
int codingTable[256];
unsigned int codingTableLen = -1;

unsigned int stateStartOffsetTable[128];
unsigned int stateCnt = 0;
int currentStateOffset = 1;  // 現在處理的state 的offset

/**
 * 本函式將解析coding table與執行Action
 */
void gvm(char * raw) {
    // 將coding table int array
    const char* d = "  ";
    char *p;
    p = strtok(raw, d);
    int idx = 0;
    while (p != NULL) {
        codingTable[idx] = atoi(p);
        idx++;
        p = strtok(NULL, d);		   
    }
    codingTableLen = idx;
    // printf("coding table size = %d \n", codingTableLen);
        
    // get state number
    stateCnt = codingTable[0];
    // printf("state number = %d \n", stateCnt);
    
    // set initial state = 0   // 固定從state0開始做
    stateStartOffsetTable[0] = +1;  // 第1個值就是state0 起始位置
    currentStateOffset = stateStartOffsetTable[0];
    
    int isParsingPhase = 1;
    while(1) {        
        // ========== version 2 ==========
        // get stateN's stateStartPtr
        //                   codingTable + OFFSET
        int* stateStartPtr = codingTable + currentStateOffset;  // !! IMPORTANT !! 🥵
        // "0" 1 35 cat 0
        int stateN = stateStartPtr[0];
        if(isParsingPhase) {
            // save the stateStartOffset
            stateStartOffsetTable[stateN] = currentStateOffset;
        }
        // get stateN's action information
        // 0 "1" 35 cat 0
        int isHaveAction = stateStartPtr[1];  // only up to 1 param supported
        unsigned int actionParamArr[4] = {0, 0, 0, 0};
        int retVarN = 0, actionN = 0, actionParamCnt = 0;
        if(isHaveAction) {
            // 0 1 "35" cat 0
            retVarN = stateStartPtr[2];
            // 0 1 35 "cat" 0
            actionN = stateStartPtr[3];
            // 0 1 35 cat "0"
            actionParamCnt = stateStartPtr[4];
            for(unsigned int i = 0; i < actionParamCnt; i++) {
                actionParamArr[i] = stateStartPtr[ 5 + i ];
            }
            // printf("action return variable number = %d \n", retVarN);
            // printf("action action number = %d \n", actionN);
            // printf("action action params number = %d \n", actionParamCnt);
            for(unsigned int i = 0; i < actionParamCnt; i++) {
                // printf("action%d param%d = %d \n", stateN, i+1, actionParamArr[i]);
            }
        }
        
        // get stateN's condition information

        if(isParsingPhase) {
            // NOTE: do NOT call action
            // NOTE: do NOT jump to next state
            int* conditionStartPtr = stateStartPtr + 5 + (actionParamCnt? 4:0);
            // if have get all state information
            if(stateStartOffsetTable[stateN] + 5 + (actionParamCnt? 4:0) >= codingTableLen)
            {
                // set phase to notParsingPhase
                isParsingPhase = 0;
                // set currentStateOffset to initial state (state0)
                currentStateOffset = stateStartOffsetTable[0];
                continue;
            }
            // set currentStateOffset state(N+1)
            int conditionType = conditionStartPtr[1];
            int conditionCnt = conditionStartPtr[2];
            switch(conditionType)
            {
                default:
                // printf("Get unexpected condition type.\n");
                Serial.println(">>>ERROR");
                break;
                
                case 0:
                while(1)
                    // printf("Condition always not pass.\n");
                break;
                
                case 1:
                // printf("The condition always pass\n");
                currentStateOffset = currentStateOffset + 5 + (actionParamCnt? 4:0) + 3;
                break;

                case 2:
                if(conditionCnt == 3)
                {
                    currentStateOffset = currentStateOffset + 5 + (actionParamCnt? 4:0) + 17;
                }
                else if(conditionCnt == 1)
                {
                    currentStateOffset = currentStateOffset + 5 + (actionParamCnt? 4:0) + 10;
                }
                else 
                    // printf("Unexpected condition count.\n");
                break;
            }
            if(currentStateOffset >= codingTableLen)
            {
                // set phase to notParsingPhase
                isParsingPhase = 0;
                // set currentStateOffset to initial state (state0)
                currentStateOffset = stateStartOffsetTable[0];
            }
        }else {
            if(isHaveAction) {
                // call action and store its return value
                unsigned int ret = callAction(actionParamCnt, actionTable[actionN], actionParamArr);
                // printf("return value = %d\n", ret);
                // get variable to store return value
                SET_CONDITION_VAR(retVarN, ret);
                // printf("return valuable = %d\n", GET_CONDITION_VAR(retVarN));
            }
            // check condition operation result
            // check next and jump to next state
            

            // deal with conditions part
            // set condition start point
            int* conditionStartPtr = stateStartPtr + 5 + (actionParamCnt? 4:0);
            if(stateStartOffsetTable[stateN] + 5 + (actionParamCnt? 4:0) >= codingTableLen)
                break;
            // 1 "2" 3
            int conditionType = conditionStartPtr[1];
            // 1 2 "3"
            int conditionCnt = conditionStartPtr[2];

            switch(conditionType)
            {
                default:
                // get unexpected condition type
                // printf("Get unexpected condition type.\n");
                Serial.println(">>>ERROR");
                break;

                case 0:
                // conditions always false
                // while(1){printf("Condition always not pass.\n");}
                break;

                case 1:
                // conditions always true
                // printf("The condition always pass, so go into next state: %d\n", conditionStartPtr[3]);
                //set the next state which should go
                currentStateOffset = stateStartOffsetTable[ conditionStartPtr[3] ];
                break;

                case 2:
                if(conditionCnt == 3)
                {
                    // have condition
                    // but three operations
                    
                    // deal with condition number 2^32bits
                    unsigned int conditionNFirst = (conditionStartPtr[5] << 24) + (conditionStartPtr[6] << 16) + (conditionStartPtr[7] << 8) + (conditionStartPtr[8]);
                    unsigned int conditionNSecond = (conditionStartPtr[11] << 24) + (conditionStartPtr[12] << 16) + (conditionStartPtr[13] << 8) + (conditionStartPtr[14]);

                    // two logical judgement
                    bool firstConditionAnswer;
                    if(conditionStartPtr[4] == 1)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) > conditionNFirst;
                    else if(conditionStartPtr[4] == 2)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) >= conditionNFirst;
                    else if(conditionStartPtr[4] == 3)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) < conditionNFirst;
                    else if(conditionStartPtr[4] == 4)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) <= conditionNFirst;
                    else if(conditionStartPtr[4] == 5)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) == conditionNFirst;
                    else if(conditionStartPtr[4] == 6)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) != conditionNFirst;
                    else
                        Serial.println(">>>ERROR");
                        // printf("Get unexpected operator.\n");
                    // printf("%d %d %u = %d\n", conditionStartPtr[3], conditionStartPtr[4], conditionNFirst, firstConditionAnswer);
                    // printf("%d %d %u = %d\n", GET_CONDITION_VAR(conditionStartPtr[3]), conditionStartPtr[4], conditionNFirst, firstConditionAnswer);
                    
                    bool secondConditionAnswer;
                    if(conditionStartPtr[10] == 1)
                        secondConditionAnswer = conditionStartPtr[9] > conditionNSecond;
                    else if(conditionStartPtr[10] == 2)
                        secondConditionAnswer = conditionStartPtr[9] >= conditionNSecond;
                    else if(conditionStartPtr[10] == 3)
                        secondConditionAnswer = conditionStartPtr[9] < conditionNSecond;
                    else if(conditionStartPtr[10] == 4)
                        secondConditionAnswer = conditionStartPtr[9] <= conditionNSecond;
                    else if(conditionStartPtr[10] == 5)
                        secondConditionAnswer = conditionStartPtr[9] == conditionNSecond;
                    else if(conditionStartPtr[10] == 6)
                        secondConditionAnswer = conditionStartPtr[9] != conditionNSecond;
                    else
                        Serial.println(">>>ERROR");
                        // printf("Get unexpected operator.\n");
                    // printf("%d %d %u = %d\n", conditionStartPtr[9], conditionStartPtr[10], conditionNSecond, secondConditionAnswer);
                    // printf("%d %d %u = %d\n", GET_CONDITION_VAR(conditionStartPtr[9]), conditionStartPtr[10], conditionNSecond, secondConditionAnswer);
                    
                    // combine two logical judgement into condition result
                    bool expressionAnswer;
                    if(conditionStartPtr[15] == 2)
                        expressionAnswer = firstConditionAnswer && secondConditionAnswer;
                    else if(conditionStartPtr[15] == 3)
                        expressionAnswer = firstConditionAnswer || secondConditionAnswer;
                    
                    // set currentStateOffset next state
                    if(expressionAnswer == true){
                        // go to next state
                        // printf("Go to next state: %d\n", conditionStartPtr[16]);
                        // follow the condition jump to the next state
                        currentStateOffset = stateStartOffsetTable[ conditionStartPtr[16] ];
                    }else {
                        // condition failed
                        // printf("Failed to go to next state: %d\n", conditionStartPtr[16]);
                        Serial.print("this state forever");
                    }
                }
                else if(conditionCnt == 1)
                {
                    // have condition
                    // only one operation

                    // deal with condition number 2^32bits
                    unsigned int conditionNFirst = (conditionStartPtr[5] << 24) + (conditionStartPtr[6] << 16) + (conditionStartPtr[7] << 8) + (conditionStartPtr[8]);
                    
                    // logical judgement into condition result
                    bool firstConditionAnswer;
                    if(conditionStartPtr[4] == 1)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) > conditionNFirst;
                    else if(conditionStartPtr[4] == 2)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) >= conditionNFirst;
                    else if(conditionStartPtr[4] == 3)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) < conditionNFirst;
                    else if(conditionStartPtr[4] == 4)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) <= conditionNFirst;
                    else if(conditionStartPtr[4] == 5)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) == conditionNFirst;
                    else if(conditionStartPtr[4] == 6)
                        firstConditionAnswer = GET_CONDITION_VAR(conditionStartPtr[3]) != conditionNFirst;
                    else
                        Serial.println(">>>ERROR");
                        // printf("Get unexpected operator.\n");
                    // printf("%d %d %u = %d\n", GET_CONDITION_VAR(conditionStartPtr[3]), conditionStartPtr[4], conditionNFirst, firstConditionAnswer);
                    
                    // set currentStateOffset next state
                    if(firstConditionAnswer == true){
                        // go to next state
                        // printf("Go to next state: %d\n", conditionStartPtr[9]);
                        // follow the condition jump to the next state
                        currentStateOffset = stateStartOffsetTable[ conditionStartPtr[9] ];
                    }else {
                        // condition failed
                        // printf("Failed to go to next state: %d\n", conditionStartPtr[9]);
                        Serial.print("this state forever");
                    }
                }else {
                    // printf("Unexpected condition count.\n");
                    Serial.print(">>>ERROR");
                }
                break;
            }
        }  // end of not isParsingPhase
        //   goto loopStart;
        // ========== version 2 end ==========
    }
}
