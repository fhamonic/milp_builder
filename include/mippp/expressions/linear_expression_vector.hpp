#ifndef MIPPP_LINEAR_EXPRESSION_HPP
#define MIPPP_LINEAR_EXPRESSION_HPP

#include <vector>

#include "mippp/concepts/linear_expression.hpp"

namespace fhamonic {
namespace mippp {

template <linear_expression_c E>
class linear_expression {
public:
    using var_id_t = typename E::var_id_t;
    using scalar_t = typename E::scalar_t;

private:
    std::vector<var_id_t> _variables;
    std::vector<var_id_t> _coeficients;
    scalar_t _constant;

public:
    constexpr linear_expression(E && e)
        : _variables(e.variables())
        , _coeficients(e.coeficients())
        , _constant(e.constant()){};

    constexpr auto variables() const noexcept { return _variables; }
    constexpr auto coeficients() const noexcept { return _coeficients; }
    constexpr scalar_type constant() const noexcept { return _constant; }
};

}  // namespace mippp
}  // namespace fhamonic

#endif  // MIPPP_LINEAR_EXPRESSION_HPP