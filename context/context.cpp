#include "common/macros.h"
#include "utils/tarslog.h"
#include "context/context.h"

namespace game
{
    namespace context
    {
        map<int, string> mSuitTran =
        {
            { 0, "d"}, { 16, "c"}, { 32, "h"}, { 48, "s"},
        };

        Context::Context() : _root(NULL)
        {
            LOG_FATAL("creator Context without root.");
        }

        Context::Context(GameRoot *root) : _root(root)
        {
            _cid_user_map.clear();
            _bankercid = nil_cid;
            _debug_cards.clear();
            _totalWeight = 0;
            _thinkTime.clear();
            gameInit();
        }

        void Context::gameInit()
        {
            roundInit();
        }

        void Context::roundInit()
        {
            this->_wallcards.clear();
            this->_tokencid = nil_cid;
            this->_winercid = nil_cid;
            this->_totalPoolNum = 0;
            this->_gamecla = false;
            this->_tokenOpTime = 0;
            this->_normal_end = true;
            this->_first_end = false;
            this->_vAiBetAction.clear();
            this->_lBeginTime = 0;
            gameDetails.clear_ibankerid();
            gameDetails.clear_ismallblind();
            gameDetails.clear_ibigblind();
            gameDetails.clear_ltotalpool();
            gameDetails.clear_commcards();
            gameDetails.clear_userinfo();
            gameDetails.clear_stepinfo();
            gameDetails.clear_calinfo();
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                it->second.roundInit();
            }
        }

        void Context::addUser(guid_t uid, cid_t cid, bool robot)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                // DLOG_TRACE("user exist, uid = " << uid);
            }

            _cid_user_map.insert(std::make_pair(cid, User(uid, cid, robot)));
        }

        void Context::delUser(guid_t uid)
        {
            cid_t cid = getCidByUid(uid);
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                _cid_user_map.erase(it);
            }
            else
            {
                // DLOG_TRACE("user isn't exist, uid = " << uid);
            }
        }

        cid_t Context::getCidByUid(guid_t uid)
        {
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (it->second._uid == uid)
                {
                    return it->second._cid;
                }
            }

            return nil_cid;
        }

        guid_t Context::getUidByCid(cid_t cid)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                return it->second._uid;
            }

            return nil_uid;
        }

        User *Context::getUserByUid(guid_t uid)
        {
            auto it = _cid_user_map.find(getCidByUid(uid));
            if (it != _cid_user_map.end())
            {
                return &(it->second);
            }

            return NULL;
        }

        User *Context::getUserByCid(cid_t cid)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                return &(it->second);
            }

            return NULL;
        }

        cid_t Context::getNextCid(cid_t cid, int count, int direction)
        {
            for (int i = 1; i < count; i++)
            {
                cid_t temp = (count + cid + i * direction) % count;
                User *user = getUserByCid(temp);
                if (user != NULL && !user->_midsit && !user->_fold && !user->_allin)
                {
                    return temp;
                }
            }

            return cid;
        }

        cid_t Context::randomCid(cid_t cid, int count)
        {
            vector<int> cids;

            //
            for (int i = 1; i < count; i++)
            {
                User *user = getUserByCid(i);
                if (user != NULL && !user->_midsit && !user->_fold && !user->_allin)
                {
                    cids.push_back(i);
                }
            }

            //
            if (cids.size() > 0)
            {
                int randCid = nnrand(cids.size() - 1, 0);
                return cids[randCid];
            }

            return cid;
        }

        cid_t Context::setBankerCid(int maxSeatNum)
        {
            if (_bankercid == nil_cid)
            {
                _bankercid = randomCid(1, maxSeatNum);
            }
            else
            {
                _bankercid = getNextCid(_bankercid, maxSeatNum, 1);
            }
            return _bankercid;
        }

        bool Context::checkRoundBetEnd(int round)
        {
            if(_first_end)
            {
                return true;
            }

            int activenum = 0;
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if(it->second._midsit || it->second._fold )
                {
                    continue;
                }
                activenum++;
            }
            if(activenum == 1)
            {
                return true;
            }
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if(it->second._midsit || it->second._fold || it->second._allin)
                {
                    continue;
                }
                DLOG_TRACE(", roundMaxBetNum: "<< _roundMaxBetNum <<", round: "<< round << ", cid: "<< it->first << ", round bet: "<< it->second.getRoundBetNum(round) <<", done:"<<it->second.isDone());
                if(!it->second.isDone() || it->second.getRoundBetNum(round) != _roundMaxBetNum)
                {
                    return false;
                }
            }
            return true;
        }

        long Context::getUserRemainMinWealth()
        {
            long remianMinWealth = -1;
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
               if (remianMinWealth == -1)
               {
                    remianMinWealth = it->second.getSHWealth();
               }
               else
               {
                    remianMinWealth = it->second.getSHWealth() < remianMinWealth ? it->second.getSHWealth(): remianMinWealth;
               }
            }
            return remianMinWealth < 0 ? 0 : remianMinWealth;
        }

        int Context::nnrand(int max, int min)
        {
            std::random_device rd;
            srand(rd());
            return min + rand() % (max - min + 1);
        }

        //机器人行为
         //0 optional map<int, vector<RobotBranch>> robotBranch;
        int Context::getRobotBranch(RoomSo::RobotAllAction &robotCfg, int round, bool isBet)
        {
            auto it = robotCfg.robotBranch.find(round);
            if(it == robotCfg.robotBranch.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].isBet == 2)
            {
                return it->second[0].addNumId;
            }
            auto itt = std::find_if(it->second.begin(), it->second.end(), [isBet](RoomSo::RobotBranch sub)->bool
            {
                return sub.isBet == (isBet ? 1 : 0);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                return itt->addNumId;
            }
            return -1;
        }

        //1 optional map<int, vector<RobotAddNum>> robotAddNum
        int Context::getRobotAddNum(RoomSo::RobotAllAction &robotCfg, int addNumId, int allAddNum)
        {
            auto it = robotCfg.robotAddNum.find(addNumId);
            if(it == robotCfg.robotAddNum.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].allAddNumMin == -1 && it->second[0].allAddNumMax == -1)
            {
                return it->second[0].selfTypeId;
            }
            auto itt = std::find_if(it->second.begin(), it->second.end(), [allAddNum](RoomSo::RobotAddNum sub)->bool
            {
                if(sub.allAddNumMax == -1)
                {
                    return allAddNum >= sub.allAddNumMin;
                }
                return allAddNum >= sub.allAddNumMin && allAddNum < sub.allAddNumMax;
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                return itt->selfTypeId;
            }
            return -1;
        }

        //2 optional map<int, vector<RobotSelfType>> robotSelfType
        int Context::getRobotSelfType(RoomSo::RobotAllAction &robotCfg, int selfTypeId, bool isBB, bool isSelfAdd, bool isSelfBet)
        {
            auto it = robotCfg.robotSelfType.find(selfTypeId);
            if(it == robotCfg.robotSelfType.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].isBB == 2 && it->second[0].isSelfAdd == 2 && it->second[0].isSelfBet == 2)
            {
                return it->second[0].wRateId;
            }
            auto itt = std::find_if(it->second.begin(), it->second.end(), [isBB, isSelfAdd, isSelfBet](RoomSo::RobotSelfType sub)->bool
            {
                return (sub.isBB == 2 || sub.isBB == (isBB ? 1 : 0)) && (sub.isSelfAdd == 2 || sub.isSelfAdd == (isSelfAdd ? 1 : 0)) && (sub.isSelfBet == 2 || sub.isSelfBet == (isSelfBet ? 1 : 0));
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                return itt->wRateId;
            }
            return -1;
        }

        //3 optional map<int, vector<RobotWRate>> robotWRate;
        int Context::getRobotWRate(RoomSo::RobotAllAction &robotCfg, int wRateId, float wRate)
        {
            auto it = robotCfg.robotWRate.find(wRateId);
            if(it == robotCfg.robotWRate.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].wRateMin == -1 && it->second[0].wRateMin == -1)
            {
                return it->second[0].roiId;
            }
            auto itt = std::find_if(it->second.begin(), it->second.end(), [wRate](RoomSo::RobotWRate sub)->bool
            {
                return (sub.wRateMin == -1 || wRate > sub.wRateMin) && (sub.wRateMax == -1 || wRate <= sub.wRateMax);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                return itt->roiId;
            }
            return -1;
        }

        //4 optional map<int, vector<RobotRoi>> robotRoi;
        int Context::getRobotRoi(RoomSo::RobotAllAction &robotCfg, int roiId, float rR)
        {
            auto it = robotCfg.robotRoi.find(roiId);
            if(it == robotCfg.robotRoi.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].roiMin == -1 && it->second[0].roiMax == -1)
            {
                return it->second[0].chipCompareId;
            }
            auto itt = std::find_if(it->second.begin(), it->second.end(), [rR](RoomSo::RobotRoi sub)->bool
            {
                return (sub.roiMin == -1 || rR >= sub.roiMin) && (sub.roiMax == -1 || rR < sub.roiMax);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                return itt->chipCompareId;
            }
            return -1;
        }
        //5 optional map<int, vector<RobotChipCompare>> robotChipCompare;
        int Context::getRobotChipCompare(RoomSo::RobotAllAction &robotCfg, int chipCompareId, long isNowGreater, long isAllGreater, long DZWealth, float wRate)
        {
            auto it = robotCfg.robotChipCompare.find(chipCompareId);
            if(it == robotCfg.robotChipCompare.end())
            {
                return -1;
            }
            int iNowGreater = DZWealth > isNowGreater ? 1 : 0;
            int iAllGreater = DZWealth > isAllGreater ? 1 : 0;
            auto itt = std::find_if(it->second.begin(), it->second.end(), [iNowGreater, iAllGreater](RoomSo::RobotChipCompare sub)->bool
            {
                return (sub.isNowGreater == 2 || iNowGreater == sub.isNowGreater) && (sub.isAllGreater == 2 || iAllGreater == sub.isAllGreater);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                if(itt->randType == 0)
                {
                    DLOG_ROBOT("step 6: randId: " <<  itt->randId << ",    oprId: " << itt->oprId);
                    return itt->oprId;
                }
                else if(itt->randType == 1)
                {
                    return getRobotWRand(robotCfg, itt->randId, wRate);
                }
                else if(itt->randType == 2)
                {
                    return getRobotNWRand(robotCfg, itt->randId);
                }
            }
            return -1;
        }

        //6 optional map<int, vector<RobotWRand>> robotWRand;
        int Context::getRobotWRand(RoomSo::RobotAllAction &robotCfg, int randId, float wRate)
        {
            auto it = robotCfg.robotWRand.find(randId);
            if(it == robotCfg.robotWRand.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].minPara == -1 && it->second[0].maxPara == -1)
            {
                DLOG_ROBOT("step 6: randId: " << randId << ",    oprId: " << it->second[0].oprId);
                return it->second[0].oprId;
            }
            int R = rand() % 100 + 1;
            auto itt = std::find_if(it->second.begin(), it->second.end(), [R, wRate](RoomSo::RobotWRand sub)->bool
            {
                float minWP = ((1 - wRate) + wRate * sub.minPara) * 100;
                float maxWP = ((1 - wRate) + wRate * sub.maxPara) * 100;
                return (sub.minPara == -1 || R >= minWP) && (sub.maxPara == -1 || R <= maxWP);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                DLOG_ROBOT("step 6: randId: " << randId << ",    R: " << R << ",    wRate: " << wRate << ",    oprId: " << itt->oprId);
                return itt->oprId;
            }
            return -1;
        }
        //7 optional map<int, vector<RobotNWRand>> robotNWRand;
        int Context::getRobotNWRand(RoomSo::RobotAllAction &robotCfg, int randId)
        {
            auto it = robotCfg.robotNWRand.find(randId);
            if(it == robotCfg.robotNWRand.end())
            {
                return -1;
            }
            if(it->second.size() == 1 && it->second[0].minPara == -1 && it->second[0].maxPara == -1)
            {
                DLOG_ROBOT("step 6: randId: " << randId << ",    oprId: " << it->second[0].oprId);
                return it->second[0].oprId;
            }
            int R = rand() % 100 + 1;
            auto itt = std::find_if(it->second.begin(), it->second.end(), [R](RoomSo::RobotNWRand sub)->bool
            {
                return (sub.minPara == -1 || R >= sub.minPara) && (sub.maxPara == -1 || R <= sub.maxPara);
            });
            if(itt == it->second.end())
            {
                return -1;
            }
            else
            {
                DLOG_ROBOT("step 6: randId: " << randId << ",    R: " << R << ",    oprId: " << itt->oprId);
                return itt->oprId;
            }
            return -1;
        }
        //8 optional map<int, vector<RobotOperation>> robotOperation;
        float Context::getRobotOperation(RoomSo::RobotAllAction &robotCfg, int OprId, std::vector<int> &vResult)
        {
            auto it = robotCfg.robotOperation.find(OprId);
            if(it == robotCfg.robotOperation.end() ||  it->second.size() > 1)
            {
                return -1;
            }
            vResult.push_back(it->second[0].type);
            vResult.push_back(it->second[0].addType);
            return it->second[0].addPara;
        }

        string Context::tranCard(short card)
        {
            int suit = card & 0x00f0;
            int face = card & 0x000f;
            auto it = mSuitTran.find(suit);
            if(it == mSuitTran.end())
            {
                return "";
            }

            ostringstream os;
            if(face == 14)
            {
                os << "A";
            }
            else if(face == 13)
            {
                os << "K";
            }
            else if(face == 12)
            {
                os << "Q";
            }
            else if(face == 11)
            {
                os << "J";
            }
            else
            {
                os << face;
            }
            os << it->second;
            return os.str();
        }

        float Context::getRobotAction(RoomSo::RobotAllAction &allRobotCfg, cid_t cid, const string roomid, std::vector<int> &vResult)
        {
            auto pUser = getUserByCid(cid);
            if(pUser == nullptr)
            {
                return -1;
            }
            auto robotUserParam = pUser->getRobotUserParam();

            DLOG_ROBOT("-------------------- robot act analyze begin. id:" << pUser->getUid() << " --------------------");
            ostringstream os;
            os << ">>>>>> roomid:" << roomid << " <<<<<<";
            DLOG_ROBOT(os.str());
            os.str("");
            os << ">>>>>> handCards: ";
            for(auto card : pUser->getVecCards())
            {
                os << tranCard(card) << "|";
            }
            os << "<<<<<<";
            DLOG_ROBOT(os.str());
            auto addNumId = getRobotBranch(allRobotCfg, _robotComParam.round, _robotComParam.isBet);
            DLOG_ROBOT("step 1: round: " << _robotComParam.round << ",    isBet: " << _robotComParam.isBet << ",    addNumId: " << addNumId);
            if(addNumId < 0)
            {
                // DLOG_TRACE("vResult addNumId: " << addNumId << ", round:" << _robotComParam.round << ", isBet:" << _robotComParam.isBet);
                return -2;
            }

            auto selfTypeId = getRobotAddNum(allRobotCfg, addNumId, _robotComParam.allAddNum);
            DLOG_ROBOT("step 2: addNumId: " << addNumId << ",    allAddNum: " << _robotComParam.allAddNum << ",    selfTypeId: " << selfTypeId);
            if(selfTypeId < 0)
            {
                // DLOG_TRACE("vResult selfTypeId: " << selfTypeId << ", addNumId:" << addNumId << ", allAddNum:" << _robotComParam.allAddNum);
                return -3;
            }

            auto wRateId = getRobotSelfType(allRobotCfg, selfTypeId, robotUserParam.isBB, robotUserParam.isSelfAdd, robotUserParam.isSelfBet);
            DLOG_ROBOT("step 3: selfTypeId: " << selfTypeId << ",    isBB: " << robotUserParam.isBB << ",    isSelfAdd: " << robotUserParam.isSelfAdd << ",    isSelfBet: " << robotUserParam.isSelfBet << ",    wRateId:" << wRateId);
            if(wRateId < 0)
            {
                // DLOG_TRACE("vResult wRateId: " << wRateId << ", selfTypeId:" << selfTypeId << ", isBB:" << robotUserParam.isBB);
                return -4;
            }

            auto roiId = getRobotWRate(allRobotCfg, wRateId, robotUserParam.wRate);
            DLOG_ROBOT("step 4: wRateId: " << wRateId << ",    wRate: " << robotUserParam.wRate << ",    roiId: " << roiId);
            if(roiId < 0)
            {
                // DLOG_TRACE("vResult roiId: " << roiId << ", wRateId:" << wRateId << ", wRate:" << robotUserParam.wRate);
                return -5;
            }

            long roundBetNum = pUser->getRoundBetNum(_robotComParam.round + 1);
            long curCallBet = getRoundMaxBetNum() - roundBetNum;

            //float rR = curCallBet <= 0 ? 1 : robotUserParam.wRate * (curCallBet H+ getTotalBetnum()) / curCallBet;

            float rR = curCallBet <= 0 ? 1 : robotUserParam.wRate * ((2 * std::min(curCallBet, pUser->getSHWealth()) + getTotalPoolNum() - curCallBet) / std::min(curCallBet, pUser->getSHWealth()));
            auto chipCompareId = getRobotRoi(allRobotCfg, roiId, rR/*回报率*/);
            DLOG_ROBOT("step 5: roiId: " << roiId << ",    callbet: " << curCallBet << ",    TotalBet: " << getTotalPoolNum() << ",    RR: " << rR << ",    chipCompareId: " << chipCompareId);
            if(chipCompareId < 0)
            {
                // DLOG_TRACE("vResult chipCompareId: " << chipCompareId << ", roiId:" << roiId << ", rR:" << rR);
                return -6;
            }

            long DZWealth = pUser->getSHWealth();
            long iNowGreater = roundBetNum;
            auto OprId = getRobotChipCompare(allRobotCfg, chipCompareId, iNowGreater, pUser->getRoundBetNum(-1), DZWealth, robotUserParam.wRate);
            DLOG_ROBOT("step 7: chipCompareId: " << chipCompareId << ",    userWealth: " << DZWealth << ",    userRoundBet: " << iNowGreater << ", userTotalBet: " << pUser->getRoundBetNum(-1) << ",    OprId: " << OprId);
            if(OprId < 0)
            {
                // DLOG_TRACE("vResult OprId: " << OprId << ", iNowGreater:" << iNowGreater << ", wRate:" << robotUserParam.wRate);
                return -7;
            }

            DLOG_ROBOT("-------------------- robot act analyze end  . id:" << pUser->getUid() << " --------------------");
            return getRobotOperation(allRobotCfg, OprId, vResult);
        }

        int Context::getAiThinkTime()
        {
            if(_totalWeight <= 0) return 0;
            long randNum = rand() % _totalWeight;
            int baseNum = 0;
            DLOG_TRACE("randNum: " << randNum << ", _totalWeight:" << _totalWeight );
            for(auto item : _thinkTime){
                baseNum += item[2];
                if(baseNum >= randNum && item.size() == 3 && item[1] > 0){
                    return rand() % (item[1] - item[0]) + item[0];
                }
            }
            return rand() % 8 + 10;
        }

        guid_t Context::getRobotUid()
        {
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (it->second._robot)
                {
                    return it->second._uid;
                }
            }
            return nil_uid;
        }
    };
};
