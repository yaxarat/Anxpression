import { NgModule } from '@angular/core';

import { HealthhackSharedLibsModule, JhiAlertComponent, JhiAlertErrorComponent } from './';

@NgModule({
    imports: [HealthhackSharedLibsModule],
    declarations: [JhiAlertComponent, JhiAlertErrorComponent],
    exports: [HealthhackSharedLibsModule, JhiAlertComponent, JhiAlertErrorComponent]
})
export class HealthhackSharedCommonModule {}
