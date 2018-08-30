import React from 'react';
import './MusicMaster.css';
//import { FormGroup, FormControl, InputGroup, Glyphicon } from 'react-bootstrap';

export default class Profile extends React.Component {
  /*constructor(props) {
    super(props);
    this.state = {
      query: '',
      artist: null
    }
  }*/
  render() {
    console.log('this.props', this.props);
    let artist ={name: '', followers: {total: ''}, images: [{url: ''}], genres: []};
    if(this.props.artist != null) {
      artist=this.props.artist;
    }
    return (
      <div className="">
        <img alt="Profile" className="" src={artist.images[artist.images.length-1].url}/>
        <div>{artist.name}</div>
        <div>{artist.followers.total}</div>
        <div>
          {
            artist.genres.map((genre,k) => {
              genre = genre !==artist.genres[artist.genres.length-1]?`${genre}, `:`& ${genre}`;
              return (
                <span key={k}>{genre}</span>
              )
            })
          }
        </div>
      </div>
    );
  }
}
