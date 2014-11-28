-module(main).
-export([ main/0 ]).

read_lines(0, Lines) -> Lines;
read_lines(N, Lines) ->
    NewLines =  Lines ++ [ read_line() ],
    read_lines(N - 1, NewLines).

read_line() ->
    { ok, [ A, B ] } = io:fread("", "~d ~d"),
    { A, B }.

mod_exp_calculation(Result, Base, Exponent, Modulus) when Exponent > 0 ->
    NewResult = case Exponent rem 2 of
        1 -> (Result * Base) rem Modulus;
        _ -> Result
    end,

    NewExponent = Exponent div 2,
    NewBase = (Base * Base) rem Modulus,

    mod_exp_calculation(NewResult, NewBase, NewExponent, Modulus);
mod_exp_calculation(Result, _, _, _) -> Result.

mod_exp(Base, Exponent, Modulus) ->
    mod_exp_calculation(1, Base, Exponent, Modulus).

main() ->
    { ok, [ N ] } = io:fread("", "~d"),

    List = read_lines(N, []),
    lists:foreach(fun({ A, B }) -> io:fwrite("~p~n", [ mod_exp(A, B, 10) rem 10 ]) end, List).