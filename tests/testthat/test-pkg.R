context( "package" )

test_that( "linking from a package works", {
   
   templib <- tempfile()
   dir.create(templib)
   
   oldWd <- getwd()
   on.exit(setwd(oldWd), add = TRUE)
   setwd("pkg")
   system(paste("R CMD INSTALL --preclean --no-multiarch ",
                "--library=", shQuote(templib), " ",
                "RcppParallelTest", sep = ""),
          intern = TRUE, ignore.stderr = TRUE)
   require(RcppParallelTest, lib.loc = templib, quietly = TRUE)
   
   v <- c(1:1000)

   expect_equal( 
      sum(v), 
      parallelVectorSum(v)
   )      
})

