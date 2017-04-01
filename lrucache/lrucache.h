//
// Author: Ping Chen
// Date: 2017.04.01
//

#include <pthread.h>

#include <list>
#include <utility>
#include <stdexcept>
#include <tr1/unordered_map>

namespace lru_cache {
namespace detail {

//
// copyable class
//
class CNoCopy {
protected:
    CNoCopy() {};
    virtual ~CNoCopy() {};
private:
    CNoCopy(const CNoCopy &);
    const CNoCopy & operator=(const CNoCopy &);
};

//
// mutex class
//
class CMutex : public CNoCopy {
public:
    CMutex() {
        pthread_mutex_init(&m_mutex, NULL);
    }

    ~CMutex() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }

    pthread_mutex_t *get_mutex() {
        return &m_mutex;
    }
private:
    pthread_mutex_t m_mutex;
};

//
// guard mutex class
//
class CMutexGuard {
public:
    explicit CMutexGuard(CMutex & mutex)
        : m_mutex(mutex)
    {
        m_mutex.lock();
    }

    ~CMutexGuard() {
        m_mutex.unlock();
    }
private:
    CMutex & m_mutex;
};
} // namespace detail

//
// lrucache class NOte: thread safe
//
template <class Key, class Value>
class CLruCache : public detail::CNoCopy {
public:
    typedef typename std::pair<Key, Value> KVPair;
    typedef typename std::list<KVPair> ListKeys;
    typedef typename std::list<KVPair>::iterator ListKeysIter;
    typedef typename std::tr1::unordered_map<Key, ListKeysIter > CacheMap;
    typedef typename std::tr1::unordered_map<Key, ListKeysIter >::iterator CacheMapIter;

    explicit CLruCache(size_t max_size = 64, size_t reserve_size = 10)
        : m_maxsize(max_size), m_reserve_size(reserve_size)
    {}

    virtual ~CLruCache() {};

    size_t size() const {
        detail::CMutexGuard l(m_lock);
        return m_cache.size();
    }

    bool empty() const {
        detail::CMutexGuard l(m_lock);
        return m_cache.empty();
    }

    void clear() {
        detail::CMutexGuard l(m_lock);
        m_cache.clear();
        m_list_keys.clear();
    }

    void insert(const Key & k, const Value & v) {
        detail::CMutexGuard l(m_lock);
        CacheMapIter iter = m_cache.find(k);
        if (iter != m_cache.end()) {
            iter->second->second = v;
            m_list_keys.splice(m_list_keys.begin(), m_list_keys, iter->second);
            return;
        }

        m_list_keys.push_front(KVPair(k, v));
        m_cache[k] = m_list_keys.begin();
        prune();
    }

    bool try_get(const Key & k, Value & v) {
        detail::CMutexGuard l(m_lock);
        CacheMapIter iter = m_cache.find(k);
        if (iter == m_cache.end()) {
            return false;
        }
        m_list_keys.splice(m_list_keys.begin(), m_list_keys, iter->second);
        v = iter->second->second;
        return true;
    }

    const Value & get(const Key & k) {
        detail::CMutexGuard l(m_lock);
        CacheMapIter iter = m_cache.find(k);
        if (iter == m_cache.end()) {
            throw std::range_error("There is no such key in cache");
        }
        m_list_keys.splice(m_list_keys.begin(), m_list_keys, iter->second);
        return iter->second->second;
    }

    bool remove(const Key & k) {
        detail::CMutexGuard l(m_lock);
        CacheMapIter iter = m_cache.find(k);
        if (iter == m_cache.end()) {
            return false;
        }
        m_list_keys.erase(iter->second);
        m_cache.erase(iter);
        return true;
    }

    bool exists(const Key & k) {
        detail::CMutexGuard l(m_lock);
        return m_cache.find(k) != m_cache.end();
    }

    size_t max_size() const { return m_maxsize; }
    size_t reserve_size() const { return m_reserve_size; }
    size_t max_allow_size() const { return m_maxsize + m_reserve_size; }

private:
    size_t prune() {
        size_t max_allow_size = m_maxsize + m_reserve_size;
        if (m_maxsize == 0 || m_cache.size() < max_allow_size) {
            return 0;
        }

        size_t count = 0;
        while (m_cache.size() > m_maxsize) {
            m_cache.erase(m_list_keys.back().first);
            m_list_keys.pop_back();
            ++count;
        }
        return count;
    }

    detail::CMutex m_lock;
    CacheMap m_cache;
    ListKeys m_list_keys;
    size_t m_maxsize;
    size_t m_reserve_size;
};

} // namespace lru_cache

