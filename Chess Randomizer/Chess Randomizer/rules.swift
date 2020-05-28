//
//  rules.swift
//  Chess Randomizer
//
//  Created by Anton Marku on 5/9/20.
//  Copyright © 2020 Anton Marku. All rights reserved.
//
import Foundation
struct rules {
    var items = Set<single_piece>()
    var turn = "No One"
    var news = ""
    var Gameover = false
    var outcome = ""
    
    
    func legal_move(og_piece: single_piece, tCol: Int, tRow:Int  ) -> Bool{
        let og_r = og_piece.row
        let og_c = og_piece.col
        if((og_piece.role == "pnBlk") || (og_piece.role == "pnWht")){
            print(og_piece.col, og_piece.row, tCol, tRow)
            if(og_piece.team == "black"){
                print("black")
                if( (og_piece.col == tCol) && ((og_piece.row + 1) == tRow) ){
                    print("legal")
                    return true
                }
                else if( (og_piece.moved == false) && (og_piece.col == tCol) && ((og_piece.row + 2) == tRow) && (specific_item(col: tCol, row: tRow - 1) == nil) ){
                    return true
                }
                else if( ((tCol == og_piece.col + 1) && (tRow == og_piece.row + 1) && (specific_item(col: og_piece.col + 1, row: og_piece.row + 1) != nil)) ||
                    ((tCol == og_piece.col - 1) && (tRow == og_piece.row + 1) &&
                    (specific_item(col: og_piece.col - 1, row: og_piece.row + 1) != nil)) ){
                    return true
                }
                else{
                    return false
                }
            }
            else if(og_piece.team == "white"){
                print("white")
               if( (og_piece.col == tCol) && ((og_piece.row - 1) == tRow) ){
                print("legal")
                   return true
               }
                else if( (og_piece.moved == false) && (og_piece.col == tCol) && ((og_piece.row - 2) == tRow) && (specific_item(col: tCol, row: tRow + 1) == nil) ){
                    return true
                }
                else if( ((tCol == og_piece.col + 1) && (tRow == og_piece.row - 1) && (specific_item(col: og_piece.col + 1, row: og_piece.row - 1) != nil)) ||
                ((tCol == og_piece.col - 1) && (tRow == og_piece.row - 1) &&
                (specific_item(col: og_piece.col - 1, row: og_piece.row - 1) != nil)) ){
                    return true
                }
               else{
                return false
                }
            }
        }
        
        if(og_piece.role == "qnBlk" || og_piece.role == "qnWht"){
            print("qn")
            if(og_r == tRow){
                if(tCol < og_c){
                    for i in 1..<(og_c - tCol){
                        if(specific_item(col: og_c - i, row: tRow) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_c < tCol){
                    for i in 1..<(tCol - og_c){
                        if(specific_item(col: og_c + i, row: tRow) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            if(og_c == tCol){
                if(tRow < og_r){
                    for i in 1..<(og_r - tRow){
                        if(specific_item(col: tCol, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_r < tRow){
                    for i in 1..<(tRow - og_r){
                        if(specific_item(col: tCol, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            if(abs(og_c - tCol) == abs(og_r - tRow)){
                if(og_c < tCol && og_r < tRow){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c + i, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(tCol < og_c && tRow < og_r){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c - i, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(tCol < og_c && og_r < tRow){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c - i, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_c < tCol && tRow < og_r){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c + i, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            return false
        }
        
        if(og_piece.role == "kgBlk" || og_piece.role == "kgWht"){
            if( (og_r == tRow && og_c + 1 == tCol) ||
                (og_r + 1 == tRow && og_c + 1 == tCol) ||
                (og_r - 1 == tRow && og_c + 1 == tCol) ||
                (og_r + 1 == tRow && og_c - 1 == tCol) ||
                (og_r + 1 == tRow && og_c == tCol) ||
                (og_r - 1 == tRow && og_c == tCol) ||
                (og_r == tRow && og_c - 1 == tCol) ||
                (og_r - 1 == tRow && og_c - 1 == tCol) ){
                return true
            }
            else{
                return false
            }
        }
        
        if(og_piece.role == "bpBlk" || og_piece.role == "bpWht"){
            print("bp")
            if(abs(og_c - tCol) == abs(og_r - tRow)){
                if(og_c < tCol && og_r < tRow){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c + i, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(tCol < og_c && tRow < og_r){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c - i, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(tCol < og_c && og_r < tRow){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c - i, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_c < tCol && tRow < og_r){
                    for i in 1..<abs(og_c - tCol){
                        if(specific_item(col: og_c + i, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            else{
                return false
            }
        }
        
        if(og_piece.role == "ktBlk" || og_piece.role == "ktWht"){
            if(specific_item(col: og_c, row: og_r + 1) == nil && specific_item(col: og_c, row: og_r + 2) == nil){
                if(tRow == og_r + 2 && ((tCol == og_c + 1) || (tCol == og_c - 1)) ){
                    return true
                }
            }
            if(specific_item(col: og_c, row: og_r - 1) == nil && specific_item(col: og_c, row: og_r - 2) == nil){
                if(tRow == og_r - 2 && ((tCol == og_c + 1) || (tCol == og_c - 1)) ){
                    return true
                }
            }
            if(specific_item(col: og_c + 1, row: og_r) == nil && specific_item(col: og_c + 2, row: og_r) == nil){
                if(tCol == og_c + 2 && ((tRow == og_r + 1) || (tRow == og_r - 1)) ){
                    return true
                }
            }
            if(specific_item(col: og_c - 1, row: og_r) == nil && specific_item(col: og_c - 2, row: og_r) == nil){
                if(tCol == og_c - 2 && ((tRow == og_r + 1) || (tRow == og_r - 1)) ){
                 return true
                }
            }
            else{
                return false
            }
        }
        
        if(og_piece.role == "rkBlk" || og_piece.role == "rkWht"){
            if(og_r == tRow){
                if(tCol < og_c){
                    for i in 1..<(og_c - tCol){
                        if(specific_item(col: og_c - i, row: tRow) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_c < tCol){
                    for i in 1..<(tCol - og_c){
                        if(specific_item(col: og_c + i, row: tRow) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            if(og_c == tCol){
                if(tRow < og_r){
                    for i in 1..<(og_r - tRow){
                        if(specific_item(col: tCol, row: og_r - i) != nil){
                            return false
                        }
                    }
                    return true
                }
                if(og_r < tRow){
                    for i in 1..<(tRow - og_r){
                        if(specific_item(col: tCol, row: og_r + i) != nil){
                            return false
                        }
                    }
                    return true
                }
            }
            return false
        }
        return false
    }
    
    func specific_item(col: Int, row: Int) -> single_piece? {
        for i in items {
            if i.col == col && i.row == row {
                return i
            }
        }
        return nil
    }
    
    
    mutating func startMatch() {
        //coin flip api call to decide who starts
        var outcome = ""//stores starting team depending on coin flip
        let url = URL(string: "https://coin-flip1.p.rapidapi.com/headstails")
        guard url != nil else{
            print("url create err")
            return
        }
        var request = URLRequest(url: url!, cachePolicy: .useProtocolCachePolicy,
        timeoutInterval: 10.0)
        let header = [
            "x-rapidapi-host": "coin-flip1.p.rapidapi.com",
            "x-rapidapi-key": "e1a87d3b1amsh6eb6a015a385a1bp10fb24jsn3c1695f66e5a"
        ]
        request.allHTTPHeaderFields = header
        request.httpMethod = "GET"
        let session = URLSession.shared
        let dataTask = session.dataTask(with: request) { (data, response, error)in
            if error == nil && data != nil {
                do{
                    let dictionary = try JSONSerialization.jsonObject(with: data!, options: .mutableContainers) as? [String:String]
                    print(dictionary!)
                    if(dictionary == ["outcome":"Heads"]){ outcome = "black"}
                    else {outcome = "white"}
                }
                catch{
                    print("error parsing data")
                }
            }
        }
        dataTask.resume()
        while(outcome == ""){}//halts function while api call happens to ensure outcome                      //receives a value. otherwise turn would set to empty string
        self.turn = outcome
        print(self.turn)
        self.news = self.turn + " goes first"
        
        //randomize roles
        var items_array = ["rk", "kt", "bp", "qn", "pn"]
        items_array = items_array.shuffled()
        
        items.removeAll()
        //place items onto board
        items.insert(single_piece(col: 0, row: 0, team: "black", role: items_array[0] + "Blk", moved: false))
        items.insert(single_piece(col: 7, row: 0, team: "black", role: items_array[0] + "Blk", moved: false))
        
        items.insert(single_piece(col: 4, row: 0, team: "black", role: "kgBlk", moved: false))
        items.insert(single_piece(col: 4, row: 7, team: "white", role: "kgWht", moved: false))
        
        for index in 0...7{
            items.insert(single_piece(col: index, row: 1, team: "black", role: items_array[4] + "Blk", moved: false))
            items.insert(single_piece(col: index, row: 6, team: "white", role: items_array[4] + "Wht", moved: false))
        }
        
        items.insert(single_piece(col: 1, row: 0, team: "black", role: items_array[1] + "Blk", moved: false))
        items.insert(single_piece(col: 6, row: 0, team: "black", role: items_array[1] + "Blk", moved: false))
        
        items.insert(single_piece(col: 1, row: 7, team: "white", role: items_array[1] + "Wht", moved: false))
        items.insert(single_piece(col: 6, row: 7, team: "white", role: items_array[1] + "Wht", moved: false))
        
        items.insert(single_piece(col: 2, row: 0, team: "black", role: items_array[2] + "Blk", moved: false))
        items.insert(single_piece(col: 5, row: 0, team: "black", role: items_array[2] + "Blk", moved: false))
        
        items.insert(single_piece(col: 0, row: 7, team: "white", role: items_array[0] + "Wht", moved: false))
        items.insert(single_piece(col: 7, row: 7, team: "white", role: items_array[0] + "Wht", moved: false))
               
       items.insert(single_piece(col: 3, row: 0, team: "black", role: items_array[3] + "Blk", moved: false))
       
       items.insert(single_piece(col: 3, row: 7, team: "white", role: items_array[3] + "Wht", moved: false))

        items.insert(single_piece(col: 2, row: 7, team: "white", role: items_array[2] + "Wht", moved: false))
        items.insert(single_piece(col: 5, row: 7, team: "white", role: items_array[2] + "Wht", moved: false))
    }
    
    mutating func shift_location(start_c: Int, start_r: Int, end_c: Int, end_r: Int) {
        if(specific_item(col: start_c, row: start_r) != specific_item(col: end_c, row: end_r) && !self.Gameover){
            guard let movingPiece = specific_item(col: start_c, row: start_r) else {
                return
            }
            if(movingPiece.team == self.turn){
                if(legal_move(og_piece: movingPiece, tCol:end_c, tRow:end_r) == true){
                    if(specific_item(col: end_c, row: end_r) != nil){
                        if(movingPiece.team != specific_item(col: end_c, row: end_r)!.team){
                            items.remove(movingPiece)
                            if(specific_item(col: end_c, row: end_r) != nil){
                                if(specific_item(col: end_c, row: end_r)!.role == "kgBlk"){
                                    self.outcome = "white wins"
                                    self.Gameover = true
                                }
                                if(specific_item(col: end_c, row: end_r)!.role == "kgWht"){
                                    self.outcome = "black wins"
                                    self.Gameover = true
                                }
                                items.remove(specific_item(col: end_c, row: end_r)!)
                            }
                            if(self.turn == "white"){
                                self.turn = "black"
                                self.news = "black's turn"
                            }
                            else {
                                self.turn = "white"
                                self.news = "white's turn"
                            }
                            if((movingPiece.role == "pnBlk") && (end_r == 7)){
                                var morphs = ["qnBlk", "bpBlk", "ktBlk", "rkBlk"]
                                morphs = morphs.shuffled()
                                items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: morphs[0], moved:true))
                                self.news = "pn morphed!"
                            }
                            else if((movingPiece.role == "pnWht") && (end_r == 0)){
                                var morphs = ["qnWht", "bpWht", "ktWht", "rkWht"]
                                morphs = morphs.shuffled()
                                items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: morphs[0], moved:true))
                                self.news = "pn morphed!"
                            }
                            else{
                                items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: movingPiece.role, moved:true))
                            }
                            if(self.Gameover){
                                self.news = self.outcome
                            }
                            knock.play()
                        }
                        else{
                            self.news = "can't capture teammate"
                        }
                    }
                    else if(specific_item(col: end_c, row: end_r) == nil){
                        items.remove(movingPiece)
                        if(specific_item(col: end_c, row: end_r) != nil){
                            if(specific_item(col: end_c, row: end_r)!.role == "kgBlk"){
                                self.outcome = "white wins"
                                self.Gameover = true
                            }
                            if(specific_item(col: end_c, row: end_r)!.role == "kgWht"){
                                self.outcome = "black wins"
                                self.Gameover = true
                            }
                            items.remove(specific_item(col: end_c, row: end_r)!)
                        }
                        if(self.turn == "white"){
                            self.turn = "black"
                            self.news = "black's turn"
                        }
                        else {
                            self.turn = "white"
                            self.news = "white's turn"
                        }
                        if((movingPiece.role == "pnWht") && (end_r == 0)){
                            var morphs = ["qnWht", "bpWht", "ktWht", "rkWht"]
                            morphs = morphs.shuffled()
                            items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: morphs[0], moved:true))
                            self.news = "pn morphed!"
                        }
                        else if((movingPiece.role == "pnBlk") && (end_r == 7)){
                            var morphs = ["qnBlk", "bpBlk", "ktBlk", "rkBlk"]
                            morphs = morphs.shuffled()
                            items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: morphs[0], moved:true))
                            self.news = "pn morphed!"
                        }
                        else{
                            items.insert(single_piece(col: end_c, row: end_r, team: movingPiece.team, role: movingPiece.role, moved:true))
                        }
                        if(self.Gameover){
                            self.news = self.outcome
                        }
                        knock.play()
                    }
                    else{
                        self.news = "can't capture teammate"
                    }
                }
                else{
                    self.news = "illegal move"
                    //print("illegal move")
                }
            }
            else{
                self.news = "not your turn"
                //print("not your turn")
            }
        }
    }
}
