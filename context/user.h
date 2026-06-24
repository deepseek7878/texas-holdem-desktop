#pragma once

#include <string>
#include <map>

#include "common/nndef.h"
#include "utils/tarslog.h"

using namespace nndef;
using namespace nnuser;
using namespace nncard;
using namespace nninvalid;

namespace game
{
    namespace context
    {
        class User
        {
            //
            friend class Context;
        public:
            //机器人配置
            struct RobotUserParam
            {
                float wRate; //随机胜率
                bool isBB;  //是否大盲位
                bool isSelfAdd;//本轮自己是否加注
                bool isSelfBet;//本轮自己是否下注

                void clear()
                {
                    wRate = 0;
                    isBB = false;
                    isSelfAdd = false;
                    isSelfBet = false;
                }
            };

        private:
            User();

        public:
            explicit User(guid_t uid, cid_t cid, bool robot = false);
            ~User();

        public:
            void roundInit();

        public:
            guid_t getUid() const
            {
                return _uid;
            }
            cid_t getCid() const
            {
                return _cid;
            }
            void setCid(cid_t cid)
            {
                _cid = cid;
            }
            bool isRobot() const
            {
                return _robot;
            }
            void setRobot(bool robot, long robotid = 0)
            {
                _robot = robot;
                if(robot){
                    _robotID= robotid;
                }
            }

            long getRobotID() const
            {
                return _robotID;
            }

            inline vecc_t const &getVecCards() const
            {
                return _cards;
            }
            inline vecc_t &refVecCards()
            {
                return _cards;
            }

            inline vecc_t const &getVecSpecCards() const
            {
                return _specards;
            }
            inline vecc_t &refVecSpecCards()
            {
                return _specards;
            }

            void setDone(bool done)
            {
                _done = done;
            }
            bool isDone() const
            {
                return _done;
            }

            void setNetBroken(bool netbroken)
            {
                _netbroken = netbroken;
            }
            bool isNetBroken() const
            {
                return _netbroken;
            }

            void setLeft(bool left) 
            {
                _left = left;
            }
            bool isLeft() const
            {
                return _left;
            }

            void setGender(int gender)
            {
                _gender = gender;
            }
            int getGender() const
            {
                return _gender;
            }

            void setWealth(long wealth)
            {
                _wealth = (wealth < 0 ? 0 : wealth);
            }
            long getWealth() const
            {
                return _wealth;
            }

            void setSHWealth(long wealth)
            {
                _shwealth = (wealth < 0 ? 0 : wealth);
            }
            long getSHWealth() const
            {
                return _shwealth;
            }

            void setNick(std::string nick)
            {
                _nick = nick;
            }
            std::string getNick() const
            {
                return _nick;
            }

            void setUrl(std::string url)
            {
                _url = url;
            }
            std::string getUrl() const
            {
                return _url;
            }

            void setMidSit(bool midsit)
            {
                _midsit = midsit;
            }
            bool isMidSit() const
            {
                return _midsit;
            }

            void setAllIn(bool allin)
            {
                _allin = allin;
            }
            bool isAllIn() const
            {
                return _allin;
            }

            void setFold(bool fold)
            {
                _fold = fold;
            }
            bool isFold() const
            {
                return _fold;
            }


            void setAct(E_NN_ACT act)
            {
                _act = act;
            }
            E_NN_ACT getAct() const
            {
                return _act;
            }

            void setOption(E_NN_ACT option)
            {
                _option = option;
            }
            E_NN_ACT getOption() const
            {
                return _option;
            }

            void setTimeOut(int timeout)
            {
                _timeout = timeout;
            }
            int getTimeOut() const
            {
                return _timeout;
            }

            bool isTuoGuan()
            {
                return _tuoguan;
            }
            void setTuoGuan(bool flag)
            {
                _tuoguan = flag;
            }
           
            void setChangeNum(long changenum)
            {
                _changenum = changenum;
            }
            long getChangeNum() const
            {
                return _changenum;
            }

            void setProfitNum(long profitnum)
            {
                _profitnum = profitnum;
            }
            long getProfitNum() const
            {
                return _profitnum;
            }

            void setCardType(E_NN_TYPE cardtype)
            {
                _cardtype = cardtype;
            }
            E_NN_TYPE getCardType() const
            {
                return _cardtype;
            }

            void addRoundBetnumList(int round, long betNum)
            {
                auto it = _round_betnum_list.find(round);
                if(it == _round_betnum_list.end())
                {
                    _round_betnum_list.insert(std::make_pair(round, std::vector<long>(1, betNum)));
                }
                else
                {
                    it->second.push_back(betNum);
                }
            }

            long getRoundBetNum(int round) const
            {
                long roundBetNum = 0;
                if(round == -1) //all
                {
                    for(auto item : _round_betnum_list)
                    {
                        for(auto num : item.second)
                        {
                            roundBetNum += num;
                        }
                    }
                }
                else
                {
                    auto it = _round_betnum_list.find(round);
                    if(it != _round_betnum_list.end())
                    {
                        for(auto num : it->second)
                        {
                            roundBetNum += num;
                        }
                    }
                }
                
                return roundBetNum;
            }

            void addRoundActionList(int round, int act)
            {
                auto it = _round_action_list.find(round);
                if(it == _round_action_list.end())
                {
                    _round_action_list.insert(std::make_pair(round, std::vector<int>(1, act)));
                }
                else
                {
                    it->second.push_back(act);
                }
            }

            map<int, std::vector<int>>& getRoundActionList()
            {
                return _round_action_list;
            }

            void setInitWealth(long value)
            {
                _initWealth = value;
            }

            long getInitWealth()
            {
                return _initWealth;
            }

            vecc_t getBestCards()
            {
                return _wincards;
            }

            void setBestCards(vecc_t cards)
            {
                _wincards.clear();
                _wincards.insert(_wincards.begin(), cards.begin(), cards.end());
            } 

            template<typename T>
            void setRobotUserParam(const string varName, const string opType, T value)
            {
                if(varName == "wRate")
                {
                    _robotUserParam.wRate = value;
                }
                else if(varName == "isBB")
                {
                    _robotUserParam.isBB = value;
                }
                else if(varName == "isSelfAdd")
                {
                    _robotUserParam.isSelfAdd = value;
                }
                else if(varName == "isSelfBet")
                {
                    _robotUserParam.isSelfBet = value;
                }
                return;
            }

            template<typename T>
            T getRobotUserParam(const string varName)
            {
                if(varName == "wRate")
                {
                    return _robotUserParam.wRate;
                }
                else if(varName == "isBB")
                {
                    return _robotUserParam.isBB;
                }
                else if(varName == "isSelfAdd")
                {
                    return _robotUserParam.isSelfAdd;
                }
                else if(varName == "isSelfBet")
                {
                    return _robotUserParam.isSelfBet;
                }
                return 0;
            }

            RobotUserParam &getRobotUserParam()
            {
                return _robotUserParam;
            }

            void setDiff(int value)
            {
                _diff = value;
            }
            int getDiff()
            {
                return _diff;
            }

        protected:

            vecc_t  _cards;     //手牌

            vecc_t _specards; //指定牌

            bool    _done;
            bool    _midsit;

            bool    _fold;   //弃牌
            bool    _allin;        //allin标记
            long    _changenum;    //
            long    _profitnum;    //扣税
            E_NN_TYPE _cardtype;   //牌型
            vecc_t  _wincards;     //牌面

        protected:
            guid_t          _uid;   //uid
            cid_t           _cid;   //位置id
            bool            _robot; //是否机器人
            long            _robotID;
            std::string     _nick;  //玩家昵称
            std::string     _url;   //玩家头像url
            bool            _netbroken; //掉线标记
            bool            _left;      //离开
            int             _gender;    //性别
            long            _wealth;            //玩家财富(金币)
            long            _shwealth;          //玩家财富

        protected:

            int             _timeout;  //超时次数
            int             _roundtimeout; //整局超时次数
            bool            _tuoguan;

            E_NN_ACT        _act;
            E_NN_ACT        _option;

            int _diff;

            map<int, std::vector<long>> _round_betnum_list;//下注列表
            map<int, std::vector<int>> _round_action_list;//操作列表
            long _initWealth;//初始筹码

            RobotUserParam _robotUserParam;
        };
    };
};

