#pragma once

/*
  Last update: v2.0.0
  Versions:
    v0.1.0 — created.
    v1.0.0 — release.
    v2.0.0 — changed types, using shs::ID, added virtual destructor.
*/

#include <stdint.h>

#include "shs_ByteCollector.h"
#include "shs_types.h"
#include "shs_DTPpacket.h"


namespace shs
{
    class API;
};

/**
 * @brief Abstract base class for API handlers identified by an shs ID.
 */
class shs::API
{
public:
    /**
     * @brief Creates an API handler with the given identifier.
     */
    explicit API(const shs::t::shs_ID_t id) : API_ID(id) {}

    /**
     * @brief Copies the API identifier from another handler.
     */
    API(const API& other) : API_ID(other.API_ID) {}

    /**
     * @brief Moves the API identifier from another handler.
     */
    API(API&& other) : API_ID(other.API_ID) { other.API_ID = {}; }

    /**
     * @brief Releases API resources.
     */
    virtual ~API() = default;


    /**
     * @brief Handles an incoming packet payload and returns a response packet.
     */
    [[nodiscard]] virtual shs::DTPpacket handle(shs::ByteCollectorReadIterator<>& it) = 0;

    /**
     * @brief Identifier of this API handler.
     */
    shs::t::shs_ID_t API_ID{};


    /**
     * @brief Compares API identifiers.
     */
    bool operator<(const shs::API& other) const { return API_ID < other.API_ID; }

    /**
     * @brief Compares API identifiers.
     */
    bool operator>(const shs::API& other) const { return API_ID > other.API_ID; }

    /**
     * @brief Checks whether two handlers have the same identifier.
     */
    bool operator==(const shs::API& other) const { return API_ID == other.API_ID; }

    /**
     * @brief Checks whether two handlers have different identifiers.
     */
    bool operator!=(const shs::API& other) const { return API_ID != other.API_ID; }
};


