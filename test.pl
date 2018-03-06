%L (long,n) pair< long , int>

l([p(0,0),p(0,0),p(11,2),p(1211,4),p(111122,6)]).

%I position in L
%Lr is after move
%P is the player (1 ou 2)
move(I, L, Lr, P):-
	nth(I,L,p(X,N)),N<6, 
	Xx is X*10+P, Nx is N+1,
	updateL(L,I,p(Xx,Nx),Lr),!.

nth(0,[K|_],K):-!.
nth(I,[_|L],K):-Ix is I - 1, nth(Ix,L,K).

updateL([_|L],0,K,[K|L]):-!.
updateL([X|L],I,K,[X|Ls]):-Ix is I -1, updateL(L,Ix,K,Ls).
