#pragma once

namespace Contact {
    enum class CollisionType { None, Top, Middle, Bottom };

    struct Contact {
        CollisionType type;
        float penetration;
    }
}  // namespace Contact