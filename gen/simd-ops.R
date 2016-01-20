path <- "inst/include/RcppParallel/simd/ops.h"
dir.create(dirname(path), recursive = TRUE, showWarnings = FALSE)

forEach <- function(data, f) {
   nm <- names(data)
   for (i in seq_along(data)) {
      f(nm[[i]], data[[i]])
   }
}

indent <- function(code, indent = "    ") {
   code <- paste(indent, code, sep = "")
   gsub("\n", "    \n", code, fixed = TRUE)
}

template <- paste(c(
   "// Auto-generated functors for functions provided by Boost.SIMD.",
   "// See 'gen/simd-ops.R' for implementation.",
   "",
   "namespace boost {",
   "namespace simd {",
   "namespace ops {",
   "",
   "%s",
   "",
   "} // namespace ops",
   "} // namespace simd",
   "} // namespace boost"
), collapse = "\n")

code <- NULL

# NOTE: Each function should accept a parameter called 'data'.
unary <- list(
   sum = "return sum(data);"
)

unary_template <- paste(c(
   "struct %s {",
   "template <typename T>",
   "inline T operator()(const T& data) {",
   "%s",
   "}",
   "};",
   ""
), collapse = "\n")

forEach(unary, function(name, value) {
   code <<- c(code, sprintf(unary_template, name, indent(value)))
})

binary <- list(
   plus = "return lhs + rhs;",
   minus = "return lhs - rhs;",
   times = "return lhs * rhs;",
   divide = "return lhs / rhs;"
)

binary_template <- paste(c(
   "struct %s {",
   "template <typename T>",
   "inline T operator()(const T& lhs, const T& rhs) {",
   "%s",
   "}",
   "};",
   ""
), collapse = "\n")

forEach(binary, function(name, value) {
   code <<- c(code, sprintf(binary_template, name, indent(value)))
})

compiled <- sprintf(template, paste(code, collapse = "\n"))
cat(compiled, file = path, sep = "\n")
