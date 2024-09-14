:- dynamic bullets/6.
:- dynamic fieldBounds/4.
:- dynamic bestMoveAngle/1.

bestMoveAngle(0).

setBattleField(Xmin, Xmax, Ymin, Ymax) :-
    assertz(fieldBounds(Xmin, Xmax, Ymin, Ymax)).

withinField(PointX, PointY) :-
    fieldBounds(Xmin, Xmax, Ymin, Ymax),
    PointX > Xmin, PointX < Xmax,
    PointY > Ymin, PointY < Ymax.

viewPoint(Pos1X, Pos1Y, Distance, Angle, Pos2X, Pos2Y) :- 
    Pos2X is Pos1X + Distance*sin(Angle),
    Pos2Y is Pos1Y + Distance*cos(Angle).

saveBullet(MyX, MyY, BulletSpeed, AngleToOpp, AngVelocity, Distance, Time) :-
    viewPoint(MyX, MyY, Distance, AngleToOpp, OppX, OppY),
    assertz(bullets(Time, OppX, OppY, BulletSpeed, AngleToOpp, AngVelocity)).

getBullets(Bullets) :-
    findall(bullets(Time, OppX, OppY, BulletSpeed, AngleToOpp, AngVelocity), 
            bullets(Time, OppX, OppY, BulletSpeed, AngleToOpp, AngVelocity), Bullets).

removeOldBullets(MyX, MyY, TimeNow) :-
    findall(OldTime, (bullets(OldTime, InitX, InitY, BulletSpeed, _, _), 
                        distance(MyX, MyY, InitX, InitY, Dist),
                        isOldBullet(Dist, TimeNow, OldTime, BulletSpeed)), OldBullets),
    retractOldBullets(OldBullets).

isOldBullet(Dist, TimeNow, Time, BulletSpeed) :- Dist < (TimeNow-Time+1) * BulletSpeed.

retractOldBullets([]).
retractOldBullets([OldTime|Rest]) :-
    retract(bullets(OldTime, _, _, _, _, _)),
    retractOldBullets(Rest).
    
chooseLocation(MyX, MyY, OppX, OppY, Time, DistToMove) :-
    removeOldBullets(MyX, MyY, Time),
    getBullets(Bullets),
    loopDirections(MyX, MyY, 0, Time, DistToMove, 10000, 0, Bullets, OppX, OppY).

loopDirections(MyX, MyY, MoveAngle, Time, DistToMove, LowestDanger, BestMoveAngle, Bullets, OppX, OppY) :-
    MoveAngle < 2 * pi,
    viewPoint(MyX, MyY, DistToMove, MoveAngle, NewX, NewY),
    withinField(NewX, NewY),
    distance(NewX, NewY, OppX, OppY, DistToOpp),
    calculateDanger(NewX, NewY, Danger, Bullets, DistToOpp),
    updateLowestDanger(MoveAngle, Danger, BestMoveAngle, LowestDanger, NewLowestDanger, NewBestMoveAngle),
    NewAngle is MoveAngle + pi / 18,
    loopDirections(MyX, MyY, NewAngle, Time, DistToMove, NewLowestDanger, NewBestMoveAngle, Bullets, OppX, OppY).

loopDirections(MyX, MyY, MoveAngle, Time, DistToMove, NewLowestDanger, NewBestMoveAngle, Bullets, OppX, OppY) :-
    NewAngle is MoveAngle + pi / 18,
    NewAngle < 2*pi,
    loopDirections(MyX, MyY, NewAngle, Time, DistToMove, NewLowestDanger, NewBestMoveAngle, Bullets, OppX, OppY).

loopDirections(_, _, MoveAngle, _, _, _, _, _,_,_) :-
    NewAngle is MoveAngle + pi / 18,
    NewAngle >= 2*pi.

distance(X, Y, Z, W, Dist) :- Dist is sqrt((X-Z)**2+(Y-W)**2).

calculateDanger(NewX, NewY, Danger, Bullets, DistToOpp) :-
    calculateTotalDanger(Bullets, NewX, NewY, Danger, DistToOpp).

calculateTotalDanger([], _,_, Danger, DistToOpp) :-
    Danger is 1 / DistToOpp**2.

calculateTotalDanger([Bullet | RestBullets], X, Y, Danger, DistToOpp) :-
    calculateBulletDanger(Bullet, X, Y, BulletDanger),
    calculateTotalDanger(RestBullets, X, Y, RestDanger, DistToOpp),
    Danger is BulletDanger + RestDanger.

calculateBulletDanger(bullets(_, OppX, OppY, _, Angle, AngVelocity), X, Y, Danger) :-
    distance(X, Y, OppX, OppY, Dist),
    viewPoint(OppX, OppY, Dist, Angle, PX, PY),
    viewPoint(OppX, OppY, Dist, Angle + AngVelocity, PLX, PLY),
    distance(X, Y, PX, PY, PDist),
    distance(X, Y, PLX, PLY, PLDist),
    Danger is (1 / PDist**2) +
             (1 / PLDist**2).

updateLowestDanger(MoveAngle, Danger, BestMoveAngle, LowestDanger, NewLowestDanger, NewBestMoveAngle) :-
    (Danger < LowestDanger ->
        NewLowestDanger is Danger,
        NewBestMoveAngle is MoveAngle
    ; 
        NewLowestDanger is LowestDanger,
        NewBestMoveAngle is BestMoveAngle
    ),
    retractall(bestMoveAngle(_)), 
    assertz(bestMoveAngle(NewBestMoveAngle)). 