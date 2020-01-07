prop_hcat xs = hcat xs == glue xs
    where
        glue []     = empty
        glue (d:ds) = d <> glue ds

