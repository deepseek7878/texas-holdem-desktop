#include "context/user.h"
#include "utils/tarslog.h"

namespace game
{
    namespace context
    {
        User::User()
            : _uid(nil_uid)
            , _cid(nil_cid)
            , _nick("")
            , _url("")
            , _netbroken(false)
            , _left(false)
            , _gender(0)
            , _wealth(0)
            , _shwealth(0)
        {
            roundInit();
        }

        User::User(guid_t uid, cid_t cid, bool robot)
            : _uid(uid)
            , _cid(cid)
            , _robot(robot)
            , _nick("")
            , _url("")
            , _netbroken(false)
            , _left(false)
            , _gender(0)
            , _wealth(0)
            , _shwealth(0)
        {
            roundInit();
        }


        void User::roundInit()
        {
            this->_cards.clear();
            this->_specards.clear();
            this->_done             = false;
            this->_midsit           = false;
            this->_fold             = false;
            this->_allin            = false;
            this->_act              = nil_act;
            this->_option           = nil_act;
            this->_changenum        = 0;
            this->_profitnum        = 0;
            this->_cardtype         = nil_nntype;
            this->_wincards.clear();
            this->_round_betnum_list.clear();
            this->_round_action_list.clear();
            this->_initWealth = 0;
            this->_robotUserParam.clear();
            this->_diff = 0;
        }

        User::~User()
        {
        }
    };
};
