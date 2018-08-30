import React from 'react';
import './MusicMaster.css';
import Profile from './Profile';
import { FormGroup, FormControl, InputGroup, Glyphicon } from 'react-bootstrap';

export default class MusicMaster extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      query: '',
      artist: null
    }
  }
  search() {
    console.log(this.state.query);


const access_token = 'BQDNKnAA_2gudf6ptM90d9xwOhVUVAG-KquiSJ5kiTQzQ1PgJ-xXB50CzFSikgpzsAr-XmJ8B9Nrlp9DW0lohu5UskgQDhzswkorF16pZLINcxQmN8BHaKUJ_LzpelBPCyPn0nP8eLVJhG7NTkX-KE3lpqH7HbNPorepq7_S-1ILvdv5PA&refresh_token=AQBgQ4yXN3CaXvBb704fNBUqyzasUEJlbSb_OR7FBQ6TJ2aUc30bELHq0mKMS5l55Wo7N7YGkrJeV0-FYCLsf44EIhoKa_CeFq0oaxdIRxJjxQ-bSSRw-vX0OdzFOa8YVYA';
    const BASE_URL = 'https://api.spotify.com/v1/search?';
    const FETCH_URL = BASE_URL + 'q=' + this.state.query
                      + '&type=artist&limit=1';
    console.log('FETCH_URL',FETCH_URL);
    fetch(FETCH_URL, {
      method: 'GET',
      headers:{
        'Authorization': 'Bearer '+ access_token
      },
      mode: 'cors',
      cache: 'default'
    })
    .then(response =>
    /*console.log('response',response.json));*/
    response.json())
    .then(json => {
      const artist = json.artists.items[0];
      console.log('artist',artist);
      this.setState({artist: artist});});
  }

  render() {
    return(
      <div className="App">
        <div>
          <input placeholder="Search An Artist..."/>
          <button className="btn">Submit</button>
        </div>

        <FormGroup>
          <InputGroup>
            <FormControl type="text" placeholder="Search an Artist..." value={this.state.query}
              onChange={event => {this.setState({query: event.target.value})}}
              onKeyPress={event => {
                if(event.key === 'Enter') {
                  this.search()
                }
              }}/>
            <InputGroup.Addon onClick={this.search.bind(this)}>
              <Glyphicon glyph="search"></Glyphicon>
            </InputGroup.Addon>
          </InputGroup>
        </FormGroup>

        <Profile
          artist={this.state.artist}/>
      </div>
    );
  }
}
