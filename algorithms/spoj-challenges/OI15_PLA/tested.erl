-module(tested).
-export([ main/0 ]).

read_building() ->
    { ok, [ _, H ] } = io:fread("", "~d ~d"),
    H.

read_buildings(0, Buildings) -> Buildings;
read_buildings(N, Buildings) ->
    NewBuildings = [ read_building() | Buildings ],
    read_buildings(N - 1, NewBuildings).

pop_until_top_of_stack_is_greater_than(_, []) -> [];
pop_until_top_of_stack_is_greater_than(Actual, Stack) when hd(Stack) > Actual ->
    pop_until_top_of_stack_is_greater_than(Actual, tl(Stack));
pop_until_top_of_stack_is_greater_than(_, Stack) -> Stack.

decision(Previous, Actual, Stack, Result) when Actual < Previous ->
    NewStack = pop_until_top_of_stack_is_greater_than(Actual, Stack),

    NewResult = case length(NewStack) of
        0 -> Result + 1;
        _ -> case hd(NewStack) of
            Actual -> Result;
            _ -> Result + 1
        end
    end,

    { NewResult, [ Actual | NewStack ] };
decision(Previous, Actual, Stack, Result) when Actual > Previous -> { Result + 1, [ Actual | Stack ] };
decision(_, _, Stack, Result) -> { Result, Stack }.

step(List, _, Index, Result) when Index > length(List) -> Result;
step(List, Stack, Index, Result) ->
    Previous = lists:nth(Index - 1, List),
    Actual = lists:nth(Index, List),

    { NewResult, NewStack } = decision(Previous, Actual, Stack, Result),

    step(List, NewStack, Index + 1, NewResult).

calculate([]) -> 0;
calculate(List) ->
    step(List, [ hd(List) ], 2, 1).

main() ->
    { ok, [ N ] } = io:fread("", "~d"),

    List = read_buildings(N, []),
    Result = calculate(List),

    io:fwrite("~p~n", [ Result ]).