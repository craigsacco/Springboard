#pragma once

#include <Springboard/Common.hpp>
#include <ch.h>

namespace Springboard {
namespace Kernel {

template <typename T, int Size>
class Mailbox
{
public:
    Mailbox()
    {
        chMBObjectInit(&mMailbox, mData, Size);
    }

    inline void Reset()
    {
        chMBReset(&mMailbox);
    }

    inline void ResetI()
    {
        chMBResetI(&mMailbox);
    }

    inline void Resume()
    {
        chMBResumeX(&mMailbox);
    }

    inline void Post(T& data)
    {
        msg_t result = chMBPost(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK, "cannot post into mailbox");
    }

    inline void PostI(T& data)
    {
        msg_t result = chMBPostI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK, "cannot post into mailbox");
    }

    inline void PostAhead(T& data)
    {
        msg_t result = chMBPostAhead(&mMailbox, (msg_t)&data, TIME_INFINITE);
        ASSERT(result == MSG_OK, "cannot post into mailbox");
    }

    inline void PostAheadI(T& data)
    {
        msg_t result = chMBPostAheadI(&mMailbox, (msg_t)&data);
        ASSERT(result == MSG_OK, "cannot post into mailbox");
    }

    inline T& Fetch()
    {
        msg_t data = 0;
        msg_t result = chMBFetch(&mMailbox, &data, TIME_INFINITE);
        ASSERT(result == MSG_OK, "cannot fetch from mailbox");
        return *((T*)data);
    }

    inline T& FetchI()
    {
        msg_t data = 0;
        msg_t result = chMBFetchI(&mMailbox, &data);
        ASSERT(result == MSG_OK, "cannot fetch from mailbox");
        return *((T*)data);
    }

private:
    mailbox_t mMailbox;
    msg_t mData[Size];
};

}
}
