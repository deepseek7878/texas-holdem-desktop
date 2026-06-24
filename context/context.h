#pragma once

#include <map>

#include "common/nndef.h"
#include "context/user.h"
#include "third.pb.h"

//
using namespace nndef;
using namespace nnuser;

namespace game
{
    class GameRoot;

    namespace context
    {
        struct RobotComParam
        {
            int round; //轮数
            bool isBet;//是否有人下注
            int allAddNum;//本轮所有玩家累积加注次数
            void clear()
            {
                round = 0;
                isBet = false;
                allAddNum = 0;
            }
        };
        //
        class Context
        {
            DISALLOW_COPY_AND_ASSIGN(Context)
        private:
            Context();
            explicit Context(GameRoot *root);

        public:
            //
            static Context *Create(GameRoot *root)
            {
                return new Context(root);
            }
            //
            void gameInit();
            //
            void roundInit();
            //
            inline GameRoot const *getRoot()
            {
                return _root;
            }

            inline vecc_t const &getVecWallCard() const
            {
                return _wallcards;
            }
            //
            inline vecc_t &refVecWallCard()
            {
                return _wallcards;
            }

            inline std::map<cid_t, User> const &getUserMap() const
            {
                return _cid_user_map;
            }
            //
            inline std::map<cid_t, User> &refUserMap()
            {
                return _cid_user_map;
            }
        public:
            //
            void addUser(guid_t uid, cid_t cid, bool robot = false);
            //
            void delUser(guid_t uid);

            cid_t getCidByUid(guid_t uid);
            //
            guid_t getUidByCid(cid_t cid);
            //
            User *getUserByUid(guid_t uid);
            //
            User *getUserByCid(cid_t cid);

            cid_t getNextCid(cid_t cid, int count, int direction);

            cid_t randomCid(cid_t cid, int count);

            cid_t setBankerCid(int maxSeatNum);

            cid_t getBankerCid()
            {
                return _bankercid;
            }

            void setTokenCid(cid_t tokencid)
            {
                _tokencid = tokencid;
            }

            cid_t getTokenCid()
            {
                return _tokencid;
            }

            void setTokenOpTime()
            {
                _tokenOpTime = time(nullptr);
            }

            long getTokenOpTime()
            {
                return _tokenOpTime;
            }

            long getTotalPoolNum()
            {
                return _totalPoolNum;
            }

            void addTotalPoolNum(long value)
            {
                _totalPoolNum += value;
            }

            long getRoundMaxBetNum()
            {
                return _roundMaxBetNum;
            }

            void setRoundMaxBetNum(long num)
            {
                _roundMaxBetNum = num;
            }
            bool checkRoundBetEnd(int round);

            long getUserRemainMinWealth();

            void setGameCal(bool flag)
            {
                _gamecla = flag;
            }
            bool getGameCal()
            {
                return _gamecla;
            }
            void addDebugCard(cid_t cid, short card)
            {
                auto it = _debug_cards.find(cid);
                if(it == _debug_cards.end())
                {
                    _debug_cards.insert(std::make_pair(cid, std::vector<short>(1, card)));
                }
                else
                {
                    it->second.push_back(card);
                }
            }
            void getDebugCardsByCid(cid_t cid, vecc_t& hdcards)
            {
                auto it = _debug_cards.find(cid);
                if(it != _debug_cards.end() && it->second.size() > 0)
                {
                    hdcards.insert(hdcards.begin(), it->second.begin(), it->second.end());
                }
            }
            void clearDebugCards()
            {
                _debug_cards.clear();
            }

            bool isNormalEnd()
            {
                return _normal_end;
            }

            void setNormalEnd(bool flag)
            {
                _normal_end = flag;
            }

            void setFirstEnd(bool flag)
            {
                _first_end = flag;
            }

            bool getFirstEnd()
            {
                return _first_end;
            }

            void setWinnerCid(cid_t cid)
            {
                _winercid = cid;
            }

            cid_t getWinnerCid()
            {
                return _winercid;
            }

            void setTotalProfit(long profit)
            {
                _totalprofit = profit;
            }

            long getTotalProft()
            {
                return _totalprofit;
            }

            //机器人行为逻辑
            template<typename T>
            void setRobotComParam(const string varName, const string opType, T value)
            {
                if(varName == "round")
                {
                    _robotComParam.round = value;
                }
                else if(varName == "isBet")
                {
                    _robotComParam.isBet = value;
                }
                else if(varName == "allAddNum")
                {
                    if(opType == "set")
                    {
                        _robotComParam.allAddNum = value;
                    }
                    else if(opType == "add")
                    {
                        _robotComParam.allAddNum += value;
                    }
                    else
                    {

                    }
                }
                return ;
            }

            template<typename T>
            T getRobotComParam(const string varName)
            {
                if(varName == "round")
                {
                    return _robotComParam.round;
                }
                else if(varName == "isBet")
                {
                    return _robotComParam.isBet;
                }
                else if(varName == "allAddNum")
                {
                    return _robotComParam.allAddNum;
                }
                return 0;
            }


            int getRobotBranch(RoomSo::RobotAllAction &robotCfg, int round, bool isBet);
            int getRobotAddNum(RoomSo::RobotAllAction &robotCfg, int addNumId, int allAddNum);
            int getRobotSelfType(RoomSo::RobotAllAction &robotCfg, int selfTypeId, bool isBB, bool isSelfAdd, bool isSelfBet);
            int getRobotWRate(RoomSo::RobotAllAction &robotCfg, int wRateId, float wRate);
            int getRobotRoi(RoomSo::RobotAllAction &robotCfg, int roiId, float rR);
            int getRobotChipCompare(RoomSo::RobotAllAction &robotCfg, int chipCompareId, long isNowGreater, long isAllGreater, long DZWealth, float wRate);
            int getRobotWRand(RoomSo::RobotAllAction &robotCfg, int randId, float wRate);
            int getRobotNWRand(RoomSo::RobotAllAction &robotCfg, int randId);
            float getRobotAction(RoomSo::RobotAllAction &allRobotCfg, cid_t cid, const string roomid, std::vector<int> &vResult);
            float getRobotOperation(RoomSo::RobotAllAction &robotCfg, int OprId, std::vector<int> &vResult);
            string tranCard(short card);

            void setAiThinkTime(long totalWeight, std::vector<std::vector<int> > &thinkTime)
            {
                _thinkTime.clear();
                _totalWeight = totalWeight;
                _thinkTime = thinkTime;
            }

            int getAiThinkTime();

            guid_t getRobotUid();

            Pb::GameDetails& getGameDetails()
            {
                return gameDetails;
            }

            void setAiBetAction(std::vector<long> &aiBetAction)
            {
                _vAiBetAction.clear();
                _vAiBetAction = aiBetAction;
            }
            std::vector<long>& getAiBetAction()
            {
                return _vAiBetAction;
            }

            void setBeginTime(long value){
                _lBeginTime = value;
            }

            long getBeginTime(){
                return _lBeginTime;
            }

        private:
            //
            int nnrand(int max, int min = 0);

        protected:
            GameRoot *const _root;
            vecc_t _wallcards;

            std::map<cid_t, User> _cid_user_map;

            cid_t _bankercid; //庄家
            cid_t _tokencid;  //当前玩家
            cid_t _winercid;  //控牌赢家
            long _totalprofit; // 机器人总收益

            long _tokenOpTime; //当前玩家开始操作时间   

            long _totalPoolNum; //池子总压注
            long _roundMaxBetNum; //本轮最大压注

            bool _gamecla;  //本局是否已经结算

            map<int, vecc_t> _debug_cards;

            bool _normal_end;

            bool _first_end;

            //ai
            long _totalWeight;
            std::vector<std::vector<int> > _thinkTime;
            std::vector<long> _vAiBetAction;

            RobotComParam         _robotComParam;

            long _lBeginTime;

            Pb::GameDetails gameDetails;
 
        public:

        };
    };
};

