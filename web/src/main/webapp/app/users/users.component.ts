import { Component, OnInit } from '@angular/core';
import { DataService } from '../data.service';
import { ActivatedRoute } from '@angular/router';

@Component({
    selector: 'jhi-users',
    templateUrl: './users.component.html',
    styleUrls: ['users.components.css']
})
export class UsersComponent implements OnInit {
    user$: Object;

    constructor(private route: ActivatedRoute, private data: DataService) {
        this.route.params.subscribe(params => (this.user$ = params.id));
    }

    ngOnInit() {
        this.data.getUser(this.user$).subscribe(data => (this.user$ = data));
    }
}
