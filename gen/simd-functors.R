path <- "inst/include/RcppParallel/simd/functors.h"
dir.create(dirname(path), recursive = TRUE, showWarnings = FALSE)

template <- paste(c(
   "// Auto-generated functors for functions provided by Boost.SIMD.",
   "// See 'gen/simd-functors.R' for implementation.",
   "",
   "namespace boost {",
   "namespace simd {",
   "namespace functors {",
   "",
   "%s",
   "",
   "} // namespace functors",
   "} // namespace simd",
   "} // namespace boost"
), collapse = "\n")

code <- NULL

# NOTE: Each function should accept a parameter called 'data'.
unary <- list(
   sum = "boost::simd::sum(data)"
)

unary_template <- paste(c(
   "struct %s {",
   "template <typename T>",
   "inline T operator()(const T& data) {",
   "    return %s;",
   "}",
   "};",
   ""
), collapse = "\n")

for (i in seq_along(unary)) {
   code <- c(code, sprintf(unary_template, names(unary)[i], unary[[i]]))
}

binary <- list(
   plus = "lhs + rhs",
   minus = "lhs - rhs",
   times = "lhs * rhs",
   divide = "lhs / rhs"
)

binary_template <- paste(c(
   "struct %s {",
   "template <typename T>",
   "inline T operator()(const T& lhs, const T& rhs) {",
   "    return %s;",
   "}",
   "};",
   ""
), collapse = "\n")

for (i in seq_along(binary)) {
   code <- c(code, sprintf(binary_template, names(binary)[[i]], binary[[i]]))
}

compiled <- sprintf(template, paste(code, collapse = "\n"))
cat(compiled, file = path, sep = "\n")
