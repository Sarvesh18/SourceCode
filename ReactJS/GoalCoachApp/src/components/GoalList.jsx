import React, { Component } from 'react';
import {goalRef} from '../firebase';
import {connect} from 'react-redux';
import {setGoals} from '../actions';
import GoalItem from './GoalItem';

import {bindActionCreators} from "redux";

console.log('GoalList');
class GoalList extends Component {
  componentDidMount() {
    goalRef.on('value',snap =>{
      let goals = [];
      //console.log('snap',snap);
      snap.forEach(goal => {
        const {email, title} =goal.val();
        const serviceKey=goal.key;
        console.log('GoalList componentDidMount()',goal.val(),goal.key,goals);
        goals.push({email,title,serviceKey});
      });
      console.log('GoalList goals',goals);
      this.props.setGoals(goals);
    })
  }
  render() {
    console.log("GoalList render goals",this.props.goals);
    return(
      <div>{
        this.props.goals.map((goal, index)=>{
        return(
            //<div key={index}>{goal.title}</div>
            <GoalItem key={index} goal={goal} />
          )
        })
    }</div>
  )}
}
function mapStateToProps(state) {
  console.log('GoalList mapStateToProps state',state);
  const {goals}=state;
  return {
    goals: goals
  }
}

function mapDispatchToProps(dispatch){
  return bindActionCreators({setGoals}, dispatch);
}
export default connect(mapStateToProps,mapDispatchToProps)(GoalList);//{setGoals}
