import React, { useState } from "react";
import { View, Text, StyleSheet, FlatList } from "react-native";
import { Alert } from "react-native";

let alertList = []

const show = () => {
  const Alert1 = {location:"location1", waterHeight:1, ID:'a',resolved:false}
  const Alert2 = {location:"location2", waterHeight:2, ID:'b',resolved:false}
  const Alert3 = {location:"location3", waterHeight:3, ID:'c',resolved:false}
  const Alert4 = {location:"location4", waterHeight:4, ID:'d',resolved:false}
  const Alert5 = {location:"location5", waterHeight:5, ID:'e',resolved:false}
  alertList = [Alert1, Alert2, Alert3, Alert4, Alert5]
  while(true){
  let txt = ""
  let dict = []
  for (let element of alertList){
    txt = element.location + " " + element.waterHeight + " " + element.ID + " " + element.resolved
    dict.push({key:txt})
  }

  const styles = StyleSheet.create({
    container: {
      flexGrow: 1,
      paddingTop: 30,
      alignContent: 'center',
      fontSize: 50,
      justifyContent: "space-between",
      alignItems: "center",
      backgroundColor: "#34568B",
      borderColor: "#000",
      borderWidth: 2,
      alignSelf: "center",
    },
    item: {
      padding: 10,
      fontSize: 20,
      height: 50,
      fontSize: 50
    },
  });
  
  return (
  <View style={styles.container}>
      <FlatList
        data = {dict}
        renderItem = {({item}) => <Text style={styles.item}>
          {item.key}</Text>}
        />
      
        
</View>
  );
}
}

export const isResolved = (ID) => {
  for(let element in alertList){
    if(element.ID == ID){
      if(element.resolved){
        return true
      }
      else{
        return false
      }
    }
  }
  return false
}

export const addAlert = (alert) => {
  alertList += alert
}

export const resolveAlert = (ID) => {
  for(let element in alertList){
    if(element.ID == ID){
      element.resolved = true
      return
      }
    }
  return
  }

export default show;